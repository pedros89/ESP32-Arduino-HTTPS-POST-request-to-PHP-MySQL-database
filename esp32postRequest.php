<?php

//what to do if in the post array I receive the variables temp and tempF
if(isset($_POST["temp"])&&isset($_POST["tempF"])) {
    $tempC = $_POST['temp'];
    $tempF = $_POST['tempF'];

    $servername = "sql.yourWebsite.com";                  //your hosting provider will give you this
    $username =  $db = "USERNAME TO LOG IN THE DATABASE"; //your hosting provider will give you this, in my case it is the same as database name
    $password = "mere28190";                              //your hosting provider will give you this when you create the database
    

    // Create connection
    $conn = new mysqli($servername, $username, $password, $db);
    

    // Check connection
    if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
        }
    echo "Connected successfully";

    //this is the MySQL query that inserts in the table  sensor_reading the following data, you must have created the table and the columns of the database through your php MyAdmin
    $sql = 'INSERT INTO `sensor_reading`(`user`, `temperatureC`, `temperatureF`, `date`, `hour`) VALUES ("Peter","'.$tempF.'","'.$tempC.'",now(),now())';


    if ($conn->query($sql) === TRUE) {
        echo "New record created successfully";
    } else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
}

?>
