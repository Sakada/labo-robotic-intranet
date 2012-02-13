<?php

class Template {

    private static $instances = array();

    /**
     * Static method for instantiating a singleton object.
     *
     * @return object
     */
    final public static function instance() {
        if (!isset(self::$instances['Template']))
            self::$instances['Template'] = new Template();

        return self::$instances['Template'];
    }

    final private function __clone() {
        
    }

    final protected function get_called_class() {
        $backtrace = debug_backtrace();
        return get_class($backtrace[2]['object']);
    }

    public function __construct() {
        
    }

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
                    Dir::IncludeDirectory(CSS_PATH, 'css');
                    Dir::IncludeDirectory(JS_PATH, 'js');
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
                                    <li>
                                        <form class="form-search" method="POST" action="../controllers/signin.php">
                                            <input type="text" placeholder="Email" class="input-small">
                                            <input type="password" placeholder="Password" class="input-small">
                                            <button  class="btn" type="submit">Go</button></form>
                                    </li>
                                </ul>
        <?php endif; ?>
                        </div>
                    </div>
                </div>
                <div class="container" style="margin-top: 50px;">

    <?php }

    public function Close() { ?>
                    <footer>
                        <p>&copy; Copyright SUPINFO International University</p>
                    </footer>
                </div> <!-- /container -->
            </body>
        </html>
        <?php
    }

}
?>
