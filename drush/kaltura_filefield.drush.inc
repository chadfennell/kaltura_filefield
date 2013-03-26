<?php

function kaltura_filefield_drush_command() {
  $items = array();
  $items['k-ff-check-ready'] = array(
    'callback' => 'ojibwe_kaltura_filefield_check_ready',
    'description' => dt('If kaltura update notifications are dropped, use this checn on and to update the status of kaltura files to the ready status.')
    );
  return $items;
}