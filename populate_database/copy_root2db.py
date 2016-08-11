#! /usr/bin/env python

import sys
import subprocess
import time
import tempfile
import re
import os
import os.path

def write_brf_root2csv_cfg(outcsv_fname, inroot_fname, 
                           args, config_parser):

    cernroot_fname = inroot_fname
    cernroot_trname = config_parser.get('job_config', 'cernroot_trname')
    output_fname = outcsv_fname
    brf_correction_table_fname = config_parser.get('job_config', 'brf_correction_table_fname')
    mc_weight_table_fname = config_parser.get('job_config', 'mc_weight_table_fname')

    temp = tempfile.NamedTemporaryFile(delete=False)
    temp.write('cernroot_fname = {0}\n'.format(cernroot_fname))
    temp.write('cernroot_trname = {0}\n'.format(cernroot_trname))
    temp.write('output_fname = {0}\n'.format(output_fname))
    temp.write('brf_correction_table_fname = {0}\n'.format(brf_correction_table_fname))
    temp.write('mc_weight_table_fname = {0}\n'.format(mc_weight_table_fname))
    temp.write('spmode = {0}\n'.format(args.spmode))
    temp.write('run = {0}\n'.format(args.run))
    temp.flush()
    temp.close()

    return temp

def copy_csv2db(csv_fname, i, args, config_parser):

    # create sql copy script 
    temp = tempfile.NamedTemporaryFile(delete=False)
    copy_cmd = "\copy {0} FROM '{1}' WITH CSV HEADER;\n".format(args.tblname, csv_fname)
    temp.write(copy_cmd)
    temp.flush()
    temp.close()

    # execute with psql
    verbosity_flag = "-q"
    if args.verbose and i == 0:
        verbosity_flag = "-a"
    subprocess.check_call(["psql",
                            verbosity_flag,
                            "-d", config_parser.get('job_config', 'dbname'),
                            "-f", temp.name])

    # clean up 
    os.unlink(temp.name)


if __name__ == '__main__':
    
    import argparse 
    from ConfigParser import SafeConfigParser

    parser = argparse.ArgumentParser(
            description='Copy contents of brf mode inputs from ROOT to postgres table. ')

    parser.add_argument('rootfile_dir', type=str, 
                        help='Directory containing all ROOT files. ')
    parser.add_argument('tblname', type=str, 
                        help='Table to copy to. ')
    parser.add_argument('spmode', type=str, 
                        help='spmode corresponding to the ROOT files. ')
    parser.add_argument('run', type=str, 
                        help='run corresponding to the ROOT files. ')
    parser.add_argument('--cfg_fname', default='copy_root2db.cfg',
                        help='Config file name. ')
    parser.add_argument('--verbose', action='store_true',
                        help='Increase verbosity; mainly for debugging. ')

    args = parser.parse_args()

    config_parser = SafeConfigParser()
    config_parser.read(args.cfg_fname)

    # find all root file names in `rootfile_dir`.
    # creates a list of their names joined with `rootfile_dir`
    rootfile_list = []
    for fname in os.listdir(args.rootfile_dir):
        rootfile_fname = os.path.join(args.rootfile_dir, fname)
        if os.path.isfile(rootfile_fname) and re.search('.*\.root$', fname) is not None:
               rootfile_list.append(rootfile_fname)

    print '+ Configurations: \n'
    print '  rootfile_dir: {0}'.format(args.rootfile_dir)
    print '    => found {0} root files\n'.format(len(rootfile_list))
    print '  destination database: {0}'.format(config_parser.get('job_config', 'dbname'))
    print '  destination table: {0}\n'.format(args.tblname)
    print '  branching fraction lookup table: {0}'.format(
            config_parser.get('job_config', 'brf_correction_table_fname'))
    print '  mc lumi weight lookup table: {0}\n'.format(
            config_parser.get('job_config', 'mc_weight_table_fname'))
    print '  spmode: {0}'.format(args.spmode)
    print '  run: {0}\n'.format(args.run)

    print '+ Processing jobs\n'

    start_all = time.time()

    # load each one root file at a time
    for i, root_fname in enumerate(rootfile_list):

        # create output file for brf_root2csv 
        brf_root2csv_out = tempfile.NamedTemporaryFile(delete=False)
        brf_root2csv_out.close()

        # write brf_root2csv config file
        brf_root2csv_cfg = write_brf_root2csv_cfg(
                brf_root2csv_out.name, root_fname, args, config_parser)

        if args.verbose and i == 0: 
            print '+ Contents of brf_root2csv config file for {0}:\n'.format(root_fname)
            with open(brf_root2csv_cfg.name, 'r') as f:
                for line in f:
                    print line,
            print

        # write contents of ROOT file into csv
        if args.verbose and i == 0:
            print '+ Converting ROOT to csv. \n'
        start = time.time()
        subprocess.check_call(
                [config_parser.get('job_config', 'brf_root2csv_path'), brf_root2csv_cfg.name])
        end = time.time()

        if args.verbose and i == 0: 
            print '  completed in {0} seconds. \n'.format(round(end-start_all, 2))
            m = re.search('(.*)\/(.*)\.root$', root_fname)
            debug_outfname = m.group(2) + '.csv'
            with open(debug_outfname, 'w') as w:
                with open(brf_root2csv_out.name, 'r') as f:
                    for line in f:
                        w.write(line)
            print '  => wrote csv output of {0} to {1}.\n'.format(root_fname, debug_outfname)

        # copy contents of csv to database 
        if args.verbose and i == 0:
            print '+ Copying csv to database. \n'
        start = time.time()
        copy_csv2db(brf_root2csv_out.name, i, args, config_parser)
        end = time.time()
        if args.verbose and i == 0:
            sys.stdout.write('\n')
            print '  completed in {0} seconds. \n'.format(round(end-start_all, 2))
            sys.stdout.flush()

        # cleanup
        os.unlink(brf_root2csv_cfg.name)
        os.unlink(brf_root2csv_out.name)

        sys.stdout.write('.')
        sys.stdout.flush()


    sys.stdout.write('\n\n')
    sys.stdout.flush()

    end = time.time()
    print '+ done. completed in {0} seconds. \n'.format(round(end-start_all, 2))

