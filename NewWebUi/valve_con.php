<?php
	
include "connect.php";


$id = "";
$vsta= "";
$csta= "";
$site= "Birmingham";
$zone = "C";
$engin= "Adam";
$fault= "";
$emer= "";

if (isset($_POST["id"]))
{
$id = $_POST["id"];	 
$vsta= $_POST["v"];
$csta= $_POST["c"];
$fault= $_POST["f"];
$emer= $_POST["e"];

$sql = "INSERT INTO `Valve` (`valveid`, `vstatus`, `cstatus`, `site`, `zone`, `fdesc`, `eno`, `emerpush`)
				VALUES ('".$id."', '".$vsta."', '".$csta."', '".$site."', '".$zone."', '".$fault."','".$engin."', '".$emer."');";

if ($conn->query($sql) === TRUE) {
		echo "";
} else echo "Error updating record: " . $conn->error;

}

$conn->close();


?>