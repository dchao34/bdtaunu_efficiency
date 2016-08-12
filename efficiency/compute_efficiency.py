#! /usr/bin/env python

import os
import sys
import subprocess
import time
import tempfile

from BrfWeightTable import BrfWeightTable

def compute_total_weight(fname, brf_table):

    total_dict = {}
    with open(fname, 'r') as fin:

        for line in fin:

            colvals = line.strip().split(' ')

            lumi_w = float(colvals[0])
            b1_mode, b2_mode = colvals[1], colvals[2]
            evttype = colvals[3]

            b1_brf_w = brf_table.get_weight(b1_mode)
            b2_brf_w = brf_table.get_weight(b2_mode)
            w = lumi_w * b1_brf_w * b2_brf_w

            if evttype not in total_dict:
                total_dict[evttype] = w
            else:
                total_dict[evttype] += w

    return total_dict


if __name__ == '__main__':
    
    import argparse 
    parser = argparse.ArgumentParser(description='Compute efficiency.')
    parser.add_argument('brf_weight_fname', type=str,
                        help='Branching fraction weight '
                             'configuration file name. ')
    parser.add_argument('--sample_modes_fname', default='data/s_modes.csv',
                        help='File containing mode data for the sample data. ')
    parser.add_argument('--source_modes_fname', default='data/o_modes.csv',
                        help='File containing mode data for the source data. ')

    args = parser.parse_args()

    print "+ configurations: \n"
    print "  brf_weight_fname = {0}\n".format(args.brf_weight_fname)
    sys.stdout.flush()

    brf_table = BrfWeightTable(args.brf_weight_fname)

    print "+ looping over sample data. \n"
    sys.stdout.flush()

    start = time.time()
    s_total_dict = compute_total_weight(args.sample_modes_fname, brf_table)
    end = time.time()

    print "  done. completed in {0} seconds. \n".format(round(end-start, 2))
    sys.stdout.flush()

    print "+ looping over source data. \n"
    sys.stdout.flush()

    start = time.time()
    o_total_dict = compute_total_weight(args.source_modes_fname, brf_table)
    end = time.time()

    print "  done. completed in {0} seconds. \n".format(round(end-start, 2))
    sys.stdout.flush()


    print '+ efficiencies proportions: \n'
    print '{0:<10}{1:<20}{2:<20}{3:<20}'.format('evttype', 'source w', 'sample w', 'eff')
    for i in sorted(o_total_dict.keys()):
        print '{0:<10}{1:<20}{2:<20}{3:<20}'.format(
                i, 
                o_total_dict[i], 
                s_total_dict[i], 
                s_total_dict[i]/o_total_dict[i])
    print
    sys.stdout.flush()
