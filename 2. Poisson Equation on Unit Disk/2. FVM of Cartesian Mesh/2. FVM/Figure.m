clear;
clf;
fid = fopen('FVM.txt','r');
string1=fgets(fid);
I = fscanf(fid,'%i',1);J = fscanf(fid,'%i',1);
r = fscanf(fid,'%f \n',1);

string2=fgets(fid);
IJ = fscanf(fid,'%i \n',1);
ss = fscanf(fid,'%*i %f %f %f %i \n',[4,IJ] ); 

string3=fgets(fid);
II = fscanf(fid,'%i \n',1);
ns= fscanf(fid,'%*i %i \n',[1,II] )+1;
fclose(fid);

xs=ss(1,:);ys=ss(2,:);Ts=ss(3,:);
xns=xs(ns);yns=ys(ns);Tns=Ts(ns);
T = (1 - xns.^2 - yns.^2)/4;

errT=T-Tns;
MerrT=mean(abs(errT));

xss=[xns-r;xns+r;xns+r;xns-r];
yss=[yns-r;yns-r;yns+r;yns+r];

figure (1)
axis equal
axis off
hold on 
p1=patch(xss,yss,Tns);
p1.EdgeColor='none';
%p1.FaceColor='flat';
rectangle('Position',[-1,-1,2,2],'Curvature',[1 1],'EdgeColor','r');

colorbar
colormap cool

figure (2)
axis equal
axis off
hold on 

errT=T-Tns;
MerrT=mean(abs(errT));

p2=patch(xss,yss,abs(errT));
p2.EdgeColor='none';
%p2.FaceColor='flat';

rectangle('Position',[-1,-1,2,2],'Curvature',[1 1],'EdgeColor','r');

colorbar
colormap cool


% xlabel('$x$','interpreter','latex');
% ylabel('$y$','interpreter','latex');
% xlim([-1 1]);
% ylim([-1 1]);
% xticks([-1 0 1]);yticks([-1 0 1]);



