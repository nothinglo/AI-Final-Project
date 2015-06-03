function isAllCellValid()
{
    var valid=true;
    
    for (var i=0; i<81; ++i) 
	{
  		var o=document.getElementById("i"+i);
  		var v=o.value;
  		if (v<"1" || v>"9") 
		{
			valid=false;
            break;
		}
    }
    
    return valid;
}

function checkAllRows()
{
    var valid=true;
    
    for (var i=0; i<9; ++i) 
	{
        var sum=0;
        for (var j=0; j<9; ++j)
        {
            var index=i*9+j;
            var o=document.getElementById("i"+index);
            var v=o.value;
            sum+=parseInt(v);
        }
        if (sum!=45)
        {
            valid=false;
            break;
        }
	}
    
    return valid;
}

function checkAllCols()
{
    var valid=true;
    
    for (var i=0; i<9; ++i) 
	{
        var sum=0;
        for (var j=0; j<9; ++j)
        {
            var index=j*9+i;
            var o=document.getElementById("i"+index);
            var v=o.value;
            sum+=parseInt(v);
        }
        if (sum!=45)
        {
            valid=false;
            break;
        }
	}
    
    return valid;
}

function checkAllBlocks()
{
    var valid=true;
    
    for (var i=0; i<3; ++i) 
	{
        for (var j=0; j<3; ++j) 
        {
            var sum=0;
            for (var m=0; m<3; ++m) 
            {
                for (var n=0; n<3; ++n) 
                {
                    var index=(i*3+m)*9+(j*3+n);
                    var o=document.getElementById("i"+index);
                    var v=o.value;
                    sum+=parseInt(v);
                }
            }
            if (sum!=45)
            {
                valid=false;
                break;
            }
        }
        if (!valid) break;
	}
    
    return valid;
}

function checkMySudoku() 
{
    if (isAllCellValid()==false)
        alert ("Some cells are empty or not a number!!!");
    else if (!checkAllRows())
        alert ("Some rows are invalid!!!");
	else if (!checkAllCols())
        alert ("Some cols are invalid!!!");
    else if (!checkAllBlocks())
        alert ("Some blocks are invalid!!!");
    else 
        alert ("Well done!!!");
}