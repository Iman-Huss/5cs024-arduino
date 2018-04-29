<?php
	include "connect.php";
	$sql = "SELECT * FROM `Valve` ORDER BY vtime";
	$result = $conn->query($sql);

	$count = 0;
	$totalRows = $result->num_rows;
	if ($result->num_rows > 0) {	
		while($row = $result->fetch_assoc()) 
		{
		if($count>($totalRows-10)) {
		
                $currentS = $row['vstatus'];
		switch ($currentS)
		{
		case "ERROR":
		{
			echo "<font color='red'>";
			break;
		}	
                case "FAIL":
		{
			echo "<font color='red'>";
			break;
		}	
		}
		
		echo "<br>".$row['vstatus'] . " " . $row['vtime'] . "</font>";
		}
		$count++;			      
		}  
	} else echo "0 results.";
	$conn->close();


?>



