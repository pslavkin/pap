A = dlmread("log.txt");
plot (A(:,7),A(:,1),";X;",A(:,7),A(:,2),";Y;",A(:,7),A(:,3),";Z;",A(:,7),A(:,4),";SX;",A(:,7),A(:,5),";SY;",A(:,7),A(:,6),";SZ;");

