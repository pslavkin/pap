A = dlmread("log.txt");
%A = B(12:60,:); %aceleracion insuficiente
%A = B(79:260,:); %acc suficiente
plot (A(:,7),A(:,1),"r;Pos_X  ;",A(:,7),A(:,2),"g;Pos_Y  ;",A(:,7),A(:,3),"b;Pos_Z  ;",A(:,7),A(:,4),"-xr;Vel_X  ;",A(:,7),A(:,5),"-xg;Vel_Y  ;",A(:,7),A(:,6),"-xb;Vel_Z  ;");
xlabel("tiempo [segs]");
ylabel("X,Y,Z = [mm] - Vel_X,Vel_Y,Vel_Z = [mm/seg]");
%A(:,4:6)=A(:,4:6)*200;
%plot (A(:,7),A(:,1:6),"-+k;z;")


