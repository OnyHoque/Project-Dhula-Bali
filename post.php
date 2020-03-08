<?php
    session_start();
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "dhulabali";
    $conn = new mysqli($servername, $username, $password, $dbname);
    
    if ($conn->connect_error) {
        echo "There was an error!";
    }

    $dt = date("Y/m/d").'  '.date("h:i:sa");

    $f2 = "NaN";
    $f3 = "NaN";
    $f4 = "NaN";
    $f5 = "NaN";
    $f6 = "NaN";
    $f7 = "NaN";
    $f8 = "NaN";
    $f9 = "NaN";
    $f10 = "NaN";

    if(isset($_GET['f2'])){
        $f2 = $_GET['f2'];
    }
    if(isset($_GET['f3'])){
        $f3 = $_GET['f3'];
    }
    if(isset($_GET['f4'])){
        $f4 = $_GET['f4'];
    }
    if(isset($_GET['f5'])){
        $f5 = $_GET['f5'];
    }
    if(isset($_GET['f6'])){
        $f6 = $_GET['f6'];
    }
    if(isset($_GET['f7'])){
        $f7 = $_GET['f7'];
    }
    if(isset($_GET['f8'])){
        $f8 = $_GET['f8'];
    }
    if(isset($_GET['f9'])){
        $f9 = $_GET['f9'];
    }
    if(isset($_GET['f10'])){
        $f10 = $_GET['f10'];
    }

    $sql = "INSERT INTO dhaka(datetime,f2,f3,f4,f5,f6,f7,f8,f9,f10) VALUES('$dt','$f2','$f3','$f4','$f5','$f6','$f7','$f8','$f9','$f10')";

    if($conn->query($sql))
        echo "<script> alert('Insert successful');</script>";
    else
        echo "<script> alert('Insert Failed');</script>";
?>