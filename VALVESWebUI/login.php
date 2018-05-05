<?php
	include "connect.php";
	
	$username = $_POST['user'];
	$password = $_POST['pass'];
	

	$query = "SELECT * FROM `OnlineUser` WHERE `username` = '$username' AND `passwrd` = '$password'"; 
	$result = $conn->query($query);
				
	if ($result->num_rows > 0) {
		echo"";
		while($row = $result->fetch_assoc())
		{
			
		}
		echo '<script type="text/javascript" language="javascript">
					window.open("dashboard.html", "_self");
			  </script>';
	} else echo '<script type="text/javascript" language="javascript">
					window.open("loginerror.html", "_self");
			  </script>';

	$conn->close();
?>