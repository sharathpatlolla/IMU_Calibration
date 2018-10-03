close all
clear all

% NOTE!!!!!! Comment or uncomment the below 2 lines if there is an error
teensy= serial('COM5','BaudRate',115200);
fopen(teensy);
temp=instrfind;
fclose (temp);

teensy= serial('COM5','BaudRate',115200);
fopen(teensy);
Limit=1001;
i=1;
gx=zeros(1,Limit-1);
gy=zeros(1,Limit-1);
gz=zeros(1,Limit-1);
Calibrated_gx=zeros(1,Limit-1);
Calibrated_gy=zeros(1,Limit-1);
Calibrated_gz=zeros(1,Limit-1);
TimeInMilli=zeros(1,Limit-1); 


while i<Limit
    new=fscanf(teensy,'%f');
    if size(new)~=7
        continue
    end
    
    TimeInMilli(1,i)=new(1);
    gx(1,i)=new(2);
    gy(1,i)=new(3);
    gz(1,i)=new(4);
    Calibrated_gx(1,i)=new(5);
    Calibrated_gy(1,i)=new(6);
    Calibrated_gz(1,i)=new(7);
    i=i+1;
end

fclose(teensy); 
delete(teensy);
delete(instrfindall);
clear teensy
 
figure
subplot(2,2,1)
plot(TimeInMilli,gx,'r',TimeInMilli,Calibrated_gx,'b')
xlabel('TimeInMilli')
ylabel('AngularVelocity from Gyroscope')
legend('gx','Calibrated gx')
title('Time VS (gx;Calibrated gx)')


subplot(2,2,2)
plot(TimeInMilli,gy,'r',TimeInMilli,Calibrated_gy,'b')
xlabel('TimeInMilli')
ylabel('AngularVelocity from Gyroscope')
legend('gy','Calibrated gy')
title('Time VS (gy;Calibrated gy)')

subplot(2,2,3)
plot(TimeInMilli,gz,'r',TimeInMilli,Calibrated_gz,'b')
xlabel('TimeInMilli')
ylabel('AngularVelocity from Gyroscope')
legend('gz','Calibrated gz')
title('Time VS (gz;Calibrated gz)')




