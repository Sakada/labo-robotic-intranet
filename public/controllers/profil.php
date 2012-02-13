<?php
  require_once '../common/inc/init.inc';
  if(!isset($user) OR $user->name != "invite")
    header("location:".SITE_PATH."load/signin.php");
?>