<?php

function kaltura_filefield_drush_command() {
  $items = array();
  $items['k-ff-update-local'] = array(
    'callback' => 'kaltura_filefield_update_local_status',
    'description' => dt('If kaltura update notifications are dropped, use this check on and to update the status of kaltura files to the ready status.'),
    'arguments' => array(
      'limit' => dt('An SQL Limit for the number of entries to upload to Kaltura'),
      ),
    );
  return $items;
}