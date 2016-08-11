-- download sample modes
BEGIN;

CREATE TEMPORARY TABLE S_eid AS 
SELECT 
  eid, 
  grouped_dss_evttype AS evttype
FROM 
  (SELECT eid, grouped_dss_evttype
   FROM event_labels_generic_augmented 
   WHERE grouped_dss_evttype=1 OR grouped_dss_evttype=2) AS Q1
  INNER JOIN 
  (SELECT eid FROM sideband_generic WHERE sideband=0) AS Q2
  USING (eid);

CREATE INDEX ON S_eid (eid);

CREATE TEMPORARY VIEW S_modes AS
SELECT 
  lumi_weight,
  b1_brf_mode,
  b2_brf_mode,
  evttype
FROM 
  S_eid INNER JOIN event_weights_generic_augmented USING (eid);

\copy (SELECT * FROM S_modes) TO 's_modes.csv' WITH DELIMITER ' ';

COMMIT;

-- download source modes
BEGIN;

CREATE TEMPORARY VIEW O_modes AS 
SELECT 
  lumi_weight,
  b1_brf_mode,
  b2_brf_mode,
  eventlabel AS evttype
FROM 
  raw_collection_brf_mode_mc_signal;

\copy (SELECT * FROM O_modes) TO 'o_modes.csv' WITH DELIMITER ' ';

COMMIT;


