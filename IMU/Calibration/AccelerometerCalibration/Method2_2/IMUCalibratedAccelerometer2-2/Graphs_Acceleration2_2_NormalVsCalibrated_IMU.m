close all
clear all

% NOTE!!!!!! Comment or uncomment the below 2 lines if there is an error
teensy= serial('COM3','BaudRate',115200);
fopen(teensy);
temp=instrfind;
fclose (temp);

teensy= serial('COM3','BaudRate',115200);
fopen(teensy);
Limit=1001;
i=1;
LocalGravity=9.79795;
ax=zeros(1,Limit-1);
ay=zeros(1,Limit-1);
az=zeros(1,Limit-1);
Calibrated_ax=zeros(1,Limit-1);
Calibrated_ay=zeros(1,Limit-1);
Calibrated_az=zeros(1,Limit-1);
HighlyCalibrated_ax=zeros(1,Limit-1);
HighlyCalibrated_ay=zeros(1,Limit-1);
HighlyCalibrated_az=zeros(1,Limit-1);
RealAcceleration_Uncalibrated=zeros(1,Limit-1);
RealAcceleration=zeros(1,Limit-1);
HighlyCalibrated_RealAcceleration=zeros(1,Limit-1);
TimeInMilli=zeros(1,Limit-1); 


while i<Limit
    new=fscanf(teensy,'%f');
    if size(new)~=7
        continue
    end
    
    TimeInMilli(1,i)=new(1);
    ax(1,i)=new(2);
    ay(1,i)=new(3);
    az(1,i)=new(4);
    Calibrated_ax(1,i)=new(5);
    Calibrated_ay(1,i)=new(6);
    Calibrated_az(1,i)=new(7);
    
    RealAcceleration_Uncalibrated(1,i)=LocalGravity-sqrt(ax(1,i)*ax(1,i)+ay(1,i)*ay(1,i)+az(1,i)*az(1,i));
    RealAcceleration(1,i)=LocalGravity-sqrt(Calibrated_ax(1,i)*Calibrated_ax(1,i)+Calibrated_ay(1,i)*Calibrated_ay(1,i)+Calibrated_az(1,i)*Calibrated_az(1,i));
    i=i+1;
end

fclose(teensy); 
delete(teensy);
delete(instrfindall);
clear teensy
 
figure
subplot(2,2,1)
plot(TimeInMilli,ax,'r',TimeInMilli,Calibrated_ax,'b')
xlabel('TimeInMilli')
ylabel('Acceleration')
legend('Ax','Calibrated Ax')
title('Time VS (Ax;Calibrated Ax)')


subplot(2,2,2)
plot(TimeInMilli,ay,'r',TimeInMilli,Calibrated_ay,'b')
xlabel('TimeInMilli')
ylabel('Acceleration')
legend('Ay','Calibrated Ay')
title('Time VS (Ay;Calibrated Ay)')


subplot(2,2,3)
plot(TimeInMilli,az,'r',TimeInMilli,Calibrated_az,'b')
xlabel('TimeInMilli')
ylabel('Acceleration')
legend('Az','Calibrated Az')
title('Time VS (Az;Calibrated Az)')


subplot(2,2,4)
plot(TimeInMilli,RealAcceleration_Uncalibrated,'r',TimeInMilli,RealAcceleration,'b')
xlabel('TimeInMilli')
ylabel('Acceleration')
legend('RealAcceleration Uncalibrated','RealAcceleration Calibrated')
title('Time VS (RealAcceleration Uncalibrated;RealAcceleration Calibrated)')


