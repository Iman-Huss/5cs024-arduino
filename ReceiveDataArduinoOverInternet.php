<?php
$var1 = $_GET['valveIsOpen'];
$var2 = $_GET['valveIsClose'];

$fileContent = "There is ".$var1." valveIsOpen, and ".$var2." valveIsClose. \n";

$fileStatus = file_put_contents('myFile.txt',$fileContent,FILE_APPEND);
if($fileStatus != false)
{
	echo "SUCCESS: data written to the file";
}
else
{
	echo "FAIL: could not write to file";
}
?>