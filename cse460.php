<?php

    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "dhulabali";
    $conn = new mysqli($servername, $username, $password, $dbname);

    $date = $_GET['date'];
    $lat = $_GET['lat'];
    $lng = $_GET['lng'];
    $temp = $_GET['temp'];
    $humidity = $_GET['humidity'];
    $dust = $_GET['dust'];
    $light = $_GET['light'];

    $sql = "INSERT INTO dhaka(datetime, f2, f3, f4, f5, f6, f7) VALUES('$date', '$lat', '$lng', '$temp', '$humidity', '$dust', '$light')";

    if ($conn->query($sql)) {
        // echo "<script>alert('Successful data insertion into Database.');</script>";
    }
    else
    {
        // echo "<script>alert('Failed data insertion into Database.');</script>";
    }
?>