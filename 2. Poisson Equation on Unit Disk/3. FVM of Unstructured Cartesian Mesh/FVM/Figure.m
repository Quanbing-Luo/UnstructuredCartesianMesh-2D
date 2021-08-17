clear;
clf;
fid = fopen('FVM.txt','r');

string1=fgets(fid);
ns = fscanf(fid,'%i \n',1);
ss = fscanf(fid,'%*i %f %f %f %f \n',[4,ns] ); 

fclose(fid);

xs=ss(1,:);ys=ss(2,:);rs=ss(3,:);Ts=ss(4,:);



xss=[xs-rs;xs+rs;xs+rs;xs-rs];
yss=[ys-rs;ys-rs;ys+rs;ys+rs];

figure (1)
axis equal
axis off
hold on 
p1=patch(xss,yss,Ts);
p1.EdgeColor='none';
%p1.FaceColor='flat';
rectangle('Position',[-1,-1,2,2],'Curvature',[1 1],'EdgeColor','r');

colorbar
colormap cool

figure (2)
axis equal
axis off
hold on 

T = (1 - xs.^2 - ys.^2)/4;
errT=T-Ts;
MerrT=mean(abs(errT));


p2=patch(xss,yss,abs(errT));
p2.EdgeColor='none';
p2.FaceColor='flat';

rectangle('Position',[-1,-1,2,2],'Curvature',[1 1],'EdgeColor','r');

colorbar
colormap cool


% xlabel('$x$','interpreter','latex');
% ylabel('$y$','interpreter','latex');
% xlim([-1 1]);
% ylim([-1 1]);
% xticks([-1 0 1]);yticks([-1 0 1]);



