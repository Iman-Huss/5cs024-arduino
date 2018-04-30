

// basic page to load data from database and refresh every second

<SCRIPT src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></SCRIPT>
    <SCRIPT src="https://code.jquery.com/jquery-1.12.4.js"></SCRIPT>
    <SCRIPT src="https://code.jquery.com/ui/1.12.1/jquery-ui.js"></SCRIPT>


    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->


        
<script language="javascript" type="text/javascript">
$(document).ready(function(){     // loads the data from liveupdate.php
    loadupdate();
});

function loadupdate(){ // runs the fuction loadupdate every second
    $("#valve_data").load("liveupdate.php");
    setTimeout(loadupdate, 1000); 
}
</script>
 <div id="valve_data"></div>
   