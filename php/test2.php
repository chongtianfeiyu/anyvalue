<?php

$obj=[1,2,3,4,-111,-1,-11111,1.5555,-1.11111,"dsadsdsdsads","dsdsadsadsds",["a"=>1]];
var_dump($str = av_encode($obj));
var_dump(av_decode($str));
