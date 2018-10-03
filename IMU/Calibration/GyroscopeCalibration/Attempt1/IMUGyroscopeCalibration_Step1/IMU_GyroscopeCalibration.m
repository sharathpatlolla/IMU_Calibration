close all
clear all

% NOTE!!!!!! Comment or uncomment the below 2 lines if there is an error
teensy= serial('COM5','BaudRate',115200);
fopen(teensy);
temp=instrfind;
fclose (temp);

teensy= serial('COM5','BaudRate',115200);
fopen(teensy);
Limit=1300;
NumOfReadingsTaken=200;
i=1;

ax=zeros(1,Limit-1);
ay=zeros(1,Limit-1);
az=zeros(1,Limit-1);
AngularVelocityMatrix=zeros(6,Limit-1);
TimeInMillis=zeros(1,Limit-1);
SwitchingVariable=zeros(1,Limit-1);

while i<Limit
    new=fscanf(teensy,'%f');
    if size(new)~=6
        continue
    end
    
    TimeInMillis(1,i)=new(1);
    SwitchingVariable(1,i)=new(2);
    if RowSearch(AngularVelocityMatrix,SwitchingVariable(1,i))>NumOfReadingsTaken-1
        disp("change orientation")
        continue
    end
    if new(3)>3|new(3)<-3
        continue
    end
    AngularVelocityMatrix(SwitchingVariable(1,i),i)=new(3);
    ax(1,i)=new(4);
    ay(1,i)=new(5);
    az(1,i)=new(6);
    i=i+1
    
    if i>2*NumOfReadingsTaken-1
        FullFilledRows=0;
        for checker=1:1:6
            if RowSearch(AngularVelocityMatrix,checker)>NumOfReadingsTaken-1
                FullFilledRows=FullFilledRows+1;
            end
        end
        if FullFilledRows==6
            break
        end        
    end    
end

fclose(teensy); 
delete(teensy);
delete(instrfindall);
clear teensy

PositiveG_gx=sum(AngularVelocityMatrix(1,:))/RowSearch(AngularVelocityMatrix,1);
NegativeG_gx=sum(AngularVelocityMatrix(2,:))/RowSearch(AngularVelocityMatrix,2);
PositiveG_gy=sum(AngularVelocityMatrix(3,:))/RowSearch(AngularVelocityMatrix,3);
NegativeG_gy=sum(AngularVelocityMatrix(4,:))/RowSearch(AngularVelocityMatrix,4);
PositiveG_gz=sum(AngularVelocityMatrix(5,:))/RowSearch(AngularVelocityMatrix,5);
NegativeG_gz=sum(AngularVelocityMatrix(6,:))/RowSearch(AngularVelocityMatrix,6);

BiasMatrix=[PositiveG_gx+NegativeG_gx;PositiveG_gy+NegativeG_gy;PositiveG_gz+NegativeG_gz]/2
MisalignmentMatrix=[0 PositiveG_gy-NegativeG_gy PositiveG_gz-NegativeG_gz;PositiveG_gx-NegativeG_gx 0 PositiveG_gz-NegativeG_gz;PositiveG_gx-NegativeG_gx PositiveG_gy-NegativeG_gy 0];



function y=RowSearch(p,q)
    count=1;
    y=0;
    while count-1<length(p(q,:))
        if p(q,count)~=0
            y=y+1;
        end
        count=count+1;
    end
end
