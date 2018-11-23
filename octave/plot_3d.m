A = dlmread("log.txt");
B = dlmread("open_hard.nc");
%plot3(A(:,1),A(:,2),A(:,3),"-bx;Recorrido;",B(:,2),B(:,3),B(:,4),"-rs;Original;");
plot3(B(:,2),B(:,3),B(:,4),"-rs;Original    ;");
xlabel("steps")
ylabel("steps")
zlabel("steps")
%plot3(B(:,2),B(:,3),B(:,4));
%plot3(A(:,1),A(:,2),A(:,3))

