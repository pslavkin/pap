A = dlmread("log.txt");
%A = B(12:60,:); %aceleracion insuficiente
%A = B(79:260,:); %acc suficiente
plot (A(:,7),A(:,1),"r;X;",A(:,7),A(:,2),"g;Y;",A(:,7),A(:,3),"b;Z;",A(:,7),100*A(:,4),"-xr;SX;",A(:,7),100*A(:,5),"-xg;SY;",A(:,7),100*A(:,6),"-xb;SZ;");
xlabel("tiempo");
ylabel("x,y,z = step - Sx, Sy, Sz = steps/seg");
%A(:,4:6)=A(:,4:6)*200;
%plot (A(:,7),A(:,1:6),"-+k;z;")


