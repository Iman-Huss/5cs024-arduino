
<style>
.div1 {
float: left; 
width: 33%;
padding: 10px;

box-sizing: border-box;
}

.div2 {
    width:33%;
    padding:10px;
    float:left;

    box-sizing: border-box;
}

.div3 {
    width: 33%;
    padding: 10px;
    box-sizing: border-box;
  
    float:left;
}
</style>

<?php	
	// loads session vars
	session_start();
	$servername = "mi-linux.wlv.ac.uk"; // connects to database
	$username = "1526056";
	$password = "mysql123";
	$databasename = "db1526056";

	$conn = new mysqli($servername, $username, $password, $databasename); // creates sql 

	if ($conn->connect_error) {
	    die('Connection failed: ' . $conn->connect_error);
	}


	$conn = new mysqli($servername, $username, $password, $databasename);

	if ($conn->connect_error) {
	    die('Connection failed: ' . $conn->connect_error);
	}

	$chamString = "";
	$sql = "SELECT * FROM `Valve` ORDER BY vtime";
	$result = $conn->query($sql);

	$count = 0;
	$totalRows = $result->num_rows;
	if ($result->num_rows > 0) {	
		while($row = $result->fetch_assoc())  // loops over records
		{		
		echo "<div style='width:1000px';>"; 
		if($count>($totalRows-10)) { // only shows last 10 
	
                $currentS = $row['vstatus'];
		switch ($currentS) // switch statement to show certain colours
			{
			case "ERROR": {
				echo "<font color='red'>";
				break;
				}	
                	case "FAIL": {
				echo "<font color='red'>";
				break;
				}
                		case "PASS": {
				echo "<font color='green'>";
				break;
				}
			default: {
				echo "<font color='black'>";
				}
			}
		
		if($row['cstatus']=="YES") {
		   
		   if(($count-9)==($totalRows-10)) {
			
                       
			if($_SESSION["lasttime"]!=$row['vtime']) { // sets a session var so that the alert is only shown once
				
				$message = "WARNING LIQUID IN CHAMBER";
				echo "<script type='text/javascript'>alert('$message');</script>"; // shows alert
				$_SESSION["lasttime"] = $row['vtime'];
				}
			}
		$chamString = "<font color='red'>..........CHAMBER HAS LIQUID IN..........</font>"; // set font to red
		}

                if($row['cstatus']=="NO") {
		
		$chamString = "..........Chamber is Empty..........";
		}
			
		if($row['cstatus']=="NA") {
		
		$chamString = "..........UNKNOWN!..........";
		}
		
                // write to page the data from database
		echo "<div class='div1'  >".$row['vstatus']."</div>";
                echo "<div class='div2' >". $row['vtime']."</div>";
                echo "<div class='div3' >".$chamString."</div></font></div>";
			
		}	
		$count++;			      
		}  
	

	} else echo "0 results.";
	$conn->close();

?>