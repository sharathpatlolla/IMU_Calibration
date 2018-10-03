
N=16384;
ADCx0=0.5952;
ADCy0=0.5928;
ADCz0=0.5938;
ADCx1=-0.5590;
ADCy1=-0.5616;
ADCz1=-0.5600;

px=2/(sqrt(3)*(ADCx0-ADCx1));
py=2/(sqrt(3)*(ADCy0-ADCy1));
pz=2/(sqrt(3)*(ADCz0-ADCz1));

qx=-N*(ADCx0+ADCx1)/(sqrt(3)*(ADCx0-ADCx1));
qy=-N*(ADCy0+ADCy1)/(sqrt(3)*(ADCy0-ADCy1));
qz=-N*(ADCz0+ADCz1)/(sqrt(3)*(ADCz0-ADCz1));


