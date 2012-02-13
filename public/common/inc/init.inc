<?php
// <editor-fold defaultstate="collapsed" desc="set global variable">
define("SITE_PATH", '/');
define("INC_PATH", '../common/inc');
define("CTRL_PATH", '../controllers');
define("WP_INC_PATH", '../blog/wp_includes/');
define("IMG_PATH", '../common/img/');
define("MODEL_PATH", '../common/inc/models');
define("SiteName", 'Labo-Robotique');
define("JS_PATH", '../common/js');
define("CSS_PATH", '../common/css');
setlocale(LC_ALL, 'fr_FR');
if (strtolower($_SERVER['REQUEST_URI']) == strtolower(SITE_PATH))
    header("location:" . SITE_PATH . 'load');
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="inclusion des classes de models">
require_once '../common/inc/ActiveRecord.inc';
$connections = array(
    'development' => 'mysql://user_f657b901:IdZ&)t%az^mqEF@a.db.shared.orchestra.io/db_f657b901?charset="utf8',
);

# must issue a "use" statement in your closure if passing variables
ActiveRecord\Config::initialize(function($cfg) use ($connections) {
            $cfg->set_model_directory('../common/inc/models');
            $cfg->set_connections($connections);
            $cfg->set_date_format("Y-m-d H:i:s");

# A fixer sur production lorsque le projet sera termine
            $cfg->set_default_connection('development');
        });
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="creation de la session">
session_name('LBIntranet');
session_start();
if (isset($_SESSION['user']))
    $user = $_SESSION['user'];
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="inclusion du controlleur">

$paths = explode('/', $_SERVER['SCRIPT_NAME']);
$script = $paths[count($paths) - 1];
if (is_file(CTRL_PATH . '/' . $script)) {
    include CTRL_PATH . '/' . $script;
}

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="Common function">
function Begin($title='Home', $layout=true, $showMenu=True) {
    ?>


    <!DOCTYPE html>
    <html lang="en">
        <head>
            <meta charset="ISO-8859-1">
            <title><?php print SiteName . " - " . $title ?></title>

            <!-- Le styles -->
            <?php
            if ($layout) {
                IncludeDirectory(CSS_PATH, 'css');
                IncludeDirectory(JS_PATH, 'js');
            }
            ?>
        </head>
        <body>
            <div class="navbar navbar-fixed-top">
                <div class="navbar-inner">
                    <div class="container">
                        <a class="brand" href="<?php print SITE_PATH ?>">Labo-Robotique</a>
                        <?php if ($showMenu): ?>
                            <ul class="nav">
                                <li><a href="<?php print SITE_PATH . 'load/profil.php' ?>">Mon Profil</a></li>
                                <li><a href="#">En cours de construction, nous reviendrons vite vers vous...</a></li>
                                <li><a><i class="icon-user" id="talk-show"></i>13 Talks</a></li>
                            </ul>
                        <?php endif; ?>
                    </div>
                </div>
            </div>
            <div class="container">
            <?php } ?>
            <?php

            function Close() { ?>
                <footer>
                    <p>&copy; Copyright SUPINFO International University</p>
                </footer>
            </div> <!-- /container -->
        </body>
    </html>
    <?php
}

function IncludeDirectory($Directory, $type='inc') {
    $MyDirectory = opendir($Directory) or die('Erreur');
    while ($Entry = @readdir($MyDirectory)) {
        if (is_dir($Directory . '/' . $Entry) && $Entry != '.' && $Entry != '..' && $Entry != 'lib')
            IncludeDirectory($Directory . '/' . $Entry, $type);
        else {
            if ($Entry != '.' && $Entry != '..') {
                switch ($type) {
                    case 'inc':
                        if ($Entry != 'init.inc' && $Entry != 'ActiveRecord.inc' && $Entry != 'lib') {
                            require_once $Directory . '/' . $Entry;
                        }
                        break;
                    case 'js':
                        print "<script type='text/javascript' src='" . $Directory . '/' . $Entry . "'></script>\n";
                        break;
                    case 'css':
                        print "<link rel='stylesheet' type='text/css' media='screen' href='" . $Directory . '/' . $Entry . "' />\n";
                        break;
                    default:
                        break;
                }
            }
        }
    }
    closedir($MyDirectory);
}

//@TODO create class Template to redirect, fill template, pass arguments, and reset...etc
// </editor-fold>
?>