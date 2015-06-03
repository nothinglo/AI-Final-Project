<html>
<head>
<title>Sudoku</title>
<script language="JavaScript" src="sudoku.js" type="text/javascript"></script>
<link rel="STYLESHEET" type="text/css" href="sudoku.css">
</head>
<body>

<center><form name ="form1" method ="post">
<input type = "TEXT" placeholder = "Enter the level(1~10)" size="25" name = "level" style="font-size:20px;font-family:Consolas">
<input type = "Submit" name = "Submit1" value = "Generate" style="font-size:20px;font-family:Consolas">
<br>
<br>
<input type = 'Radio' name ='way' value= 'GradientDescent' >
<label style="font-size:24px;font-family:Consolas">Gradient Descent</label>
<br>
<input type = 'Radio' name ='way' value= 'RandomWalk' style="font-family:Consolas">
<label style="font-size:24px;font-family:Consolas">RandomWalk</label>
</center></form>

<center><div id=sudoku>
<table border=0>
<tr><td>
<center><h1 class=sudoku>Sudoku</h1></center>
</td></tr>

<tr><td>
<?php
function getParameters (&$level=1, &$method=0)
{
    if(!empty($_POST)) {
        $level = (int)$_POST['level'];

        if($level > 0 && $level <= 10)
        {
            $selected_radio = $_POST['way'];
            
            if ($selected_radio == 'GradientDescent') 
            {
                $method = 0;
                return True;
            }
            else if ($selected_radio == 'RandomWalk') 
            {
                $method = 1;
                return True;
            }
            return False;
        }
        return False;
    }
    return False;
}

function getSudoku ($level=5, $method=0)
{
	$contents = "";
    if ($method == 0)
    {
        $contents = shell_exec("./sudoku-generator $level -php");
    }
    else if ($method == 1)
    {
        $contents = shell_exec("./sudoku-generator $level -a -php");
    }
	return $contents;
}

$level     = 1;
$method    = 0;

if (getParameters($level, $method))
{
    $sudokustr = getSudoku ($level, $method);
	$sudoku    = explode(";", $sudokustr);

	echo "<table cellspacing=0 cellpadding=1 border=0 bgcolor=#000000>";
	$count = 0;
	for ($x = 0; $x < 9; $x++)
	{
		echo "<tr>";
		for ($y = 0; $y < 9; $y++)
		{
			echo "<td><div class=cell>";
			$data = "";
			if ($y == 2 || $y == 5)
			{
				$border = "border-right:2px solid #000000;";
			} else {
				$border = "";	
			}	
			if ($x == 2 || $x == 5)
			{
				$border .= "border-bottom:2px solid #000000;";
			}	
			if (intval($sudoku[$count]) > 0 )
			{
				$data = "value='" . $sudoku[$count] . "' readonly style='background:#66B3FF; " . $border . "'";
			} else {
				$data = " style='" . $border . "'";
			}
			echo "\r\n<input valign=middle type=text id=i" . $count . " name=i" . $count . " " . $data . " size=5 maxlength=5 class=cell onkeyup='fontsize(this, this.value)'>\r\n";
			echo "</div></td>";
			$count ++;
		}
		echo "</tr>";
	}
	echo "</table>";
}

?>
<br>
<center><input type="submit" name="check" value="Check Answer" onclick="checkMySudoku()" style="font-size:20px;font-family:Consolas"/></center>
</td></tr>
</div></center>

</body>
</html>
