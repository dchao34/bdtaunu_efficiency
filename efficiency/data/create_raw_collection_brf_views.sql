BEGIN;

CREATE MATERIALIZED VIEW raw_collection_brf_mode_mc_signal AS 
SELECT 
  eventlabel,
  lumi_weight, 
  b1_brf_mode, 
  b2_brf_mode
FROM 
  raw_collection_brf_mode_sp1235
WHERE eventlabel=1 OR eventlabel=2 
UNION ALL
SELECT 
  eventlabel,
  lumi_weight, 
  b1_brf_mode, 
  b2_brf_mode
FROM 
  raw_collection_brf_mode_sp1235
WHERE eventlabel=1 OR eventlabel=2;

COMMIT;
