close all
clear all

%If there is an error in running this code, comment or uncomment the below 2 lines
% teensy= serial('COM3','BaudRate',115200);
% fopen(teensy);
temp=instrfind;
fclose (temp);

teensy= serial('COM3','BaudRate',115200);
fopen(teensy);
Limit=1001;
i=1;
ax=zeros(1,Limit-1);
ay=zeros(1,Limit-1);
az=zeros(1,Limit-1);
TimeInMillis=zeros(1,Limit-1);
tolerance=0.02;
LowerLimit=(1/sqrt(3))-tolerance;
UpperLimit=(1/sqrt(3))+tolerance;

while i<Limit
    new=fscanf(teensy,'%f');
    if size(new)~=4
        continue
    end
    
    TimeInMillis(1,i)=new(1);
    ax(1,i)=new(2);
    ay(1,i)=new(3);
    az(1,i)=new(4);
%     COMMENT THE NEXT 3 LINES BELOW (IF CONDITION) IF THE ANGLE IS NEGATIVE g
    if  (LowerLimit < ax(1,i)) && (ax(1,i)< UpperLimit) && (LowerLimit < ay(1,i)) && (ay(1,i)< UpperLimit) && (LowerLimit < az(1,i)) && (az(1,i)< UpperLimit)     
        i=i+1
    end
%     COMMENT THE NEXT 3 LINES BELOW (IF CONDITION) IF THE ANGLE IS POSITIVE g
%     if  (-LowerLimit > ax(1,i)) && (ax(1,i)> -UpperLimit) && (-LowerLimit > ay(1,i)) && (ay(1,i)> -UpperLimit) && (-LowerLimit > az(1,i)) && (az(1,i)> -UpperLimit)     
%     i=i+1
%     end    
end

ADC=[mean(ax),mean(ay),mean(az)]

fclose(teensy); 
delete(teensy);
delete(instrfindall);
clear teensy

