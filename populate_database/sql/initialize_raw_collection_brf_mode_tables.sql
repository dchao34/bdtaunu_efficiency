BEGIN;

CREATE TABLE raw_collection_brf_mode_sp1235 (
  eventlabel integer,
  b1_brf_mode brf_mode,
  b2_brf_mode brf_mode,
  brf_correction_weight numeric
);

CREATE TABLE raw_collection_brf_mode_sp1237 (
  eventlabel integer,
  b1_brf_mode brf_mode,
  b2_brf_mode brf_mode,
  brf_correction_weight numeric
);

COMMIT;
