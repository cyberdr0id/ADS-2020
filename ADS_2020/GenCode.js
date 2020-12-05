function MyFun(MyFuna, MyFunb)
{
var MyFunc;
MyFunc = MyFuna / MyFunb;
return MyFunc;
}

function Back(Backstr)
{
var Backme;
Backme = Backstr;
return Backme;
}


{
document.write('U can use basic user libs');
var mx;
var my;
mx = 2;
my = 12;
var mresult;
mresult = MyFun(mx, my);
document.write('<br>');
document.write(mresult);
var mspace;
mspace = ' ';
var mphrase;
mphrase = 'Compiler';
mspace = Back(mphrase);
document.write('<br>');
document.write(mspace);
var mzap;
mzap = 3 * (5 - 2) / 0 + 3 / 6;
document.write('<br>');
document.write(mzap);
}

