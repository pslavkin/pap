A = dlmread("log.txt");
B = dlmread("open_hard.nc");
%A(:,7)=A(:,7)*1.40;
%A = B(12:60,:); %aceleracion insuficiente
%A = B(79:260,:); %acc suficiente
plot (A(:,1),A(:,2),"-xr;Recorrido;",B(:,2),B(:,3),"-sg;Original;");
%plot (A(:,7),A(:,1),"r;X;",A(:,7),A(:,2),"g;Y;",A(:,7),A(:,3),"b;Z;",A(:,1),A(:,2),"-xr;X;",B(:,2),B(:,3),"-sr;OX;");

xlabel("steps");
ylabel("steps");
%xlabel("stepstiempo");
%ylabel("x,y,z = step - Sx, Sy, Sz = steps/seg");
%A(:,4:6)=A(:,4:6)*200;
%plot (A(:,7),A(:,1:6),"-+k;z;")


