CREATE TEMP VIEW errors AS
  SELECT a.eid, a.ntracks, b.lumi_weight, b.brf_correction_weight
  FROM (
    SELECT f.eid, f.ntracks 
    FROM event_level_features_generic f
    INNER JOIN (SELECT * FROM event_labels_generic WHERE eventlabel = 2) AS l
    ON (f.eid = l.eid)
  ) AS a
  INNER JOIN event_weights_generic_augmented b
  ON (a.eid = b.eid);

--SELECT sqrt(sum((weight * ntracks * 0.0024)^2) / sum(weight)^2) FROM errors; 
--SELECT sum(lumi_weight * brf_correction_weight * ntracks * 0.022) / sum(lumi_weight * brf_correction_weight) FROM errors; 
SELECT sum(lumi_weight * brf_correction_weight * 0.044) / sum(lumi_weight * brf_correction_weight) FROM errors; 

--https://bbr-wiki.slac.stanford.edu/bbr_wiki/images/f/f6/Berryhill.pdf <- 2.2% per track/particle
--at most 2 leptons per signal event, i.e. 4.4% per event conservatively.
