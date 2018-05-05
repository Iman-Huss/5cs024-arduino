<?php
	include "connect.php";
	
	$valveid = $_POST['vid'];
	
	$sql = "SELECT * FROM `Valve` WHERE `valveid` = '$valveid' && `vstatus` = 'FAIL'";
	
	$result = $conn->query($sql);
	
	if ($result->num_rows > 0) {
		echo "<table>
				<tr>
					<th>Valve ID</th>
					<th>Status</th>
					<th>Time</th>
					<th>Chamber</th>
					<th>Site</th>
					<th>Zone</th>
					<th>Engineer ID</th>
					<th>Fault?</th>
					<th>Emergency Button Pushed?</th>
				</tr>";
		while($row = $result->fetch_assoc()) 
		{
			echo "<tr>
					<td>".$row["valveid"]."</td>
					<td>".$row["vstatus"]."</td>
					<td>".$row["vtime"]."</td>
					<td>".$row["cstatus"]."</td>
					<td>".$row["site"]."</td>
					<td>".$row["zone"]."</td>
					<td>".$row["eno"]."</td>
					<td>".$row["fdesc"]."</td>
					<td>".$row["emerpush"]."</td>

				</tr>";
		}
	    echo "</table>";
	} else echo "0 results.";
	
	$conn->close();
?>