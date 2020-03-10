<?php
    session_start();
    $servername = "localhost:3306";
    $username = "innovat2_onyhoque";
    $password = "-33dz~S?L9;q";
    $dbname = "innovat2_blog";
    $conn = new mysqli($servername, $username, $password, $dbname);
    
    if ($conn->connect_error) {
        echo "There was an error!";
    }

    $status = "";

    if(isset($_GET['status'])){
        $status = $_GET['status'];
    }

    if($status == "in"){

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
    }

    if($status == "out"){
        
        $start = 0;
        if(isset($_GET['start'])){
            $start = (int)$_GET['start'];
        }

        

        $sql = "SELECT * FROM dhaka  LIMIT 100 OFFSET $start";
        $result = $conn->query($sql);
        $c = $start;
        $start += 100;
        echo '<a href="dsd.php?status=out&start='.$start.'">';
        echo "next range : ".$start. " : ".($start+100)."<br><br>";


        echo '<table border="2" cellspacing="5" cellpadding="5">';
        
        if($result){
            echo '<tr><th>Row No</th><th>datetime</th> <th>f2</th> <th>f3</th> <th>f4</th> <th>f5</th> <th>f6</th> <th>f7</th> <th>f8</th> <th>f9</th> <th>f10</th> </tr>';
            $c += 1;
            while($row = $result->fetch_assoc()){
                echo '<tr><td>'.$c.'</td> <td>'.$row["datetime"].'</td> <td>'.$row["f2"].'</td> <td>'.$row["f3"].'</td> <td>'.$row["f4"].'</td> <td>'.$row["f5"].'</td> <td>'.$row["f6"].'</td> <td>'.$row["f7"].'</td> <td>'.$row["f8"].'</td> <td>'.$row["f9"].'</td> <td>'.$row["f10"].'</td> </tr>';
                $c++;
            }
            echo '</table>';
        }
    }

    if($status == "clear"){
        $sql = "TRUNCATE TABLE dhaka";
        $result = $conn->query($sql);
        if($result){
            echo "All data deleted.";
        }
    }
?>