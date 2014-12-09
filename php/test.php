<?php
$str1 = file_get_contents('conn_anyvalue2.bin');
$str2 = file_get_contents('conn_json.txt');
$str3 = file_get_contents('conn_ig.bin');

echo microtime(true)."\n";

for($i=0;$i<100000;$i++)
{
	$obj = json_decode($str2,true);
}

echo microtime(true)."\n";

for($i=0;$i<100000;$i++)
{
	$obj = av_decode($str1);
}


echo microtime(true)."\n";

for($i=0;$i<100000;$i++)
{
	$str = av_encode($obj);
}

echo microtime(true)."\n";

for($i=0;$i<100000;$i++)
{
	$str = json_encode($obj);
}
echo microtime(true)."\n";
