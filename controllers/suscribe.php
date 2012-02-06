<?php

include_once '../common/inc/init.inc';

$result = "Veuillez remplir toutes les informations demandees";
if (isset($_POST['captcha']) && isset($_POST['vcaptcha'])) {
    if (md5($_POST['captcha']) == $_POST['vcaptcha']) {
        print '1';
        if (isset($_POST['id']) && isset($_POST['email']) && isset($_POST['firstname']) && isset($_POST['lastname']) && isset($_POST['campus']) && isset($_POST['password']) && isset($_POST['dpt']) && isset($_POST['promotion']) && isset($_POST['description'])) {
                $picture = basename($_FILES['picture']['name']);
                $newimage = SITE_PATH."var/tmp/" . $_POST['id'];
                $result = @move_uploaded_file($_FILES['image_file']['tmp_name'], $newimage);
                $user = User::create('user', array(
                            'id' => $_POST['id'],
                            'email' => strtolower($_POST['email']),
                            'firstname' => ucfirst(strtolower($_POST['firstname'])),
                            'lastname' => strtoupper($_POST['lastname']),
                            'campus_id' => $_POST['campus'],
                            'password' => sha1($_POST['password']),
                            'dpt' => $_POST['dpt'],
                            'promotion' => $_POST['promotion'],
                            'picture' => $newimage,
                            'description' => htmlspecialchars_decode($_POST['description'])
                        ));
        }
        else
            $result = "<h2 style='color :#F00'>Formulaire incomplet</h2>";
    } else {
        $result = "<h2 style='color :#F00'>erreurs captcha</h2>";
    }
    if (isset($user))
        header("location:/" . SITE_PATH . "/views/");
}
$campuses = Campus::find('all');
$nb1 = rand(1, 5);
$nb2 = rand(1, 5);
$somme = $nb1 + $nb2;
$captcha_crypted = md5($somme)
?>