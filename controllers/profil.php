<?php
  require_once '../common/inc/init.inc';
  if(!isset($user) OR $user->name != "invit�")
    header("location:".SITE_PATH."load/signin.php");
?>