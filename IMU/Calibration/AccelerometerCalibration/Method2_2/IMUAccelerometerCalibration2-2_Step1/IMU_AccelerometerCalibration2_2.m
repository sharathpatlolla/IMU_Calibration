% ALGORITHM
% 
% The values from the serial port are read and processed to calculate required matrices, the serial port either outputs 6
% values(this happens when the IMU is in 1 of the 8 required orientations) or 3 values. The matrices are calculated when the
% it outputs 6 values. 200 readings are taken in each orientation,  the acceleration vales in each orientation are stored
% in the each of the rows of AccelerationMatrix. This values are used to calculate the Bias, Scalar and Misalignment Matrices

close all
clear all

% NOTE!!!!!! Comment or uncomment the below 2 lines if there is an error
teensy= serial('COM4','BaudRate',115200);
fopen(teensy);
temp=instrfind;
fclose (temp);

teensy= serial('COM4','BaudRate',115200);
fopen(teensy);
NumOfReadingsTaken=200;
NumOfOrientationofIMU=6;
Limit=NumOfReadingsTaken*NumOfOrientationofIMU;
i=1;

ax=zeros(1,Limit-1);
ay=zeros(1,Limit-1);
az=zeros(1,Limit-1);
AccelerationMatrix=zeros(6,Limit-1);
TimeInMillis=zeros(1,Limit-1);
SwitchingVariable=zeros(1,Limit-1);
% The value of local gravity is obtained from the web and it depends on the lattitude and altitude
LocalGravity=9.79795;

while i<Limit
    new=fscanf(teensy,'%f');
% Sometimes the serial port outputs less values at that point of time. When this happens the control is passed to next loop
% using continue
    if length(new)~=6 
        if length(new)~=3
            continue
        end
    end
    
    if length(new)==6
        TimeInMillis(1,i)=new(1);
% The SwitchingVariable is used so that the acceleration values are stored in different rows for different orientations        
        SwitchingVariable(1,i)=new(2);
% If the required number of values are obtained from the orientation, it tells you to change the orientation.
        if RowSearch(AccelerationMatrix,SwitchingVariable(1,i))>NumOfReadingsTaken-1
            disp("change orientation")
            continue
        end
        
        AccelerationMatrix(SwitchingVariable(1,i),i)=new(3)*LocalGravity;
        ax(1,i)=new(4);
        ay(1,i)=new(5);
        az(1,i)=new(6);
        i=i+1      
% This if condition helps to break the loop if all the readings are taken in all orientations. It uses RowSearch function 
% to check the number of non zero elements in each row of a matrix.
        if i>Limit
            FullFilledRows=0;
            for checker=1:1:6
                if RowSearch(AccelerationMatrix,checker)>NumOfReadingsTaken-1
                    FullFilledRows=FullFilledRows+1;
                end
            end
            if FullFilledRows==6
                break
            end       
        end   
        
    else 
% The values of acceleration are displayed if the orientation is not right to help align the orientation        
        temp=[new(1) new(2) new(3)];
        disp(temp)
    end   
    
end

fclose(teensy); 
delete(teensy);
delete(instrfindall);
clear teensy

PositiveG_ax=sum(AccelerationMatrix(1,:))/RowSearch(AccelerationMatrix,1);
NegativeG_ax=sum(AccelerationMatrix(2,:))/RowSearch(AccelerationMatrix,2);
PositiveG_ay=sum(AccelerationMatrix(3,:))/RowSearch(AccelerationMatrix,3);
NegativeG_ay=sum(AccelerationMatrix(4,:))/RowSearch(AccelerationMatrix,4);
PositiveG_az=sum(AccelerationMatrix(5,:))/RowSearch(AccelerationMatrix,5);
NegativeG_az=sum(AccelerationMatrix(6,:))/RowSearch(AccelerationMatrix,6);

BiasMatrix=[PositiveG_ax+NegativeG_ax;PositiveG_ay+NegativeG_ay;PositiveG_az+NegativeG_az]/2

% The function RowSearch outputs the number of non zero values in a row of a matrix. The arguments are p(Matrix) and q(required row)
function y=RowSearch(p,q)
    count=1;
    y=0;
    while count<length(p(q,:))
        if p(q,count)~=0
            y=y+1;
        end
        count=count+1;
    end
end
