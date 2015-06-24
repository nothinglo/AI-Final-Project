<html>
<head>
<title>Sudoku</title>
<script language="JavaScript" src="sudoku.js" type="text/javascript"></script>
<link rel="STYLESHEET" type="text/css" href="sudoku.css">
</head>
<body>

<center><form name ="form1" method ="post">
<input type = 'Radio' name ='way' value= 'cluesNumber' checked="checked">
<label style="font-size:24px;font-family:Consolas">Specified Number of Clues</label>
<br><br>
<input type = "TEXT" placeholder = "Enter the clues(20~80)" size="25" name = "clues" style="font-size:20px;font-family:Consolas">
<br><br>
<input type = 'Radio' name ='way' value= 'difficulty' >
<label style="font-size:24px;font-family:Consolas">Specified Level of Difficulties</label>
<br><br>
<select name ='difficult'>
  <option value="easy" style="font-size:20px;font-family:Consolas">Easy</option>
  <option value="medium" style="font-size:20px;font-family:Consolas">Simple</option>
  <option value="hard" style="font-size:20px;font-family:Consolas">Hard</option>
  <option value="master" style="font-size:20px;font-family:Consolas">Master</option>
</select>
<br><br>
<input type = "Submit" name = "Submit1" value = "Generate" style="font-size:20px;font-family:Consolas">
</center></form>

<center><div id=sudoku>
<table border=0>
<tr><td>
<center><h1 class=sudoku>Sudoku</h1></center>
</td></tr>

<tr><td>
<?php
function getParameters (&$clues=20, &$level=1, &$method=0)
{
    if(!empty($_POST)) {
        $clues = (int)$_POST['clues'];
        
        $selected_radio = $_POST['way'];
        
        if ($selected_radio == 'cluesNumber') 
        {
            if($clues >= 20 && $clues <= 80)
            {
                $method = 0;
                return True;
            }
            else return False;
        }
        else if ($selected_radio == 'difficulty')
        {
            $selected_level = $_POST['difficult'];
            echo('<center>');
            echo($selected_level);
            echo('</center>');
            if ($selected_level == 'easy')
            {
                $method = 1;
                $level = 0;
                return True;
            }    
            else if ($selected_level == 'medium')
            {
                $method = 1;
                $level = 1;
                return True;
            }
            else if ($selected_level == 'hard')
            {
                $method = 1;
                $level = 2;
                return True;
            }
            else if ($selected_level == 'master')
            {
                $method = 1;
                $level = 3;
                return True;
            }
            else return False;
        }
        else return False;
    }
    return False;
}

function getSudoku ($clues=20, $level=5, $method=0)
{
	$contents = "";
    if ($method == 0)
    {
        $clues = 81 - $clues;
        $contents = shell_exec("./sudoku-generator $clues -s");
    }
    else if ($method == 1)
    {
        $contents = shell_exec("./sudoku-generator $level");
    }
	return $contents;
}

$level     = 0;
$clues     = 20;
$method    = 0;

if (getParameters($clues, $level, $method))
{
    $sudokustr = getSudoku ($clues, $level, $method);
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
