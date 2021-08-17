clear;
clf;
fid = fopen('CartesianMesh.txt','r');
string1=fgets(fid);
I = fscanf(fid,'%i',1);J = fscanf(fid,'%i',1);r = fscanf(fid,'%f \n',1);

string2=fgets(fid);
IJ = fscanf(fid,'%i \n',1);
ss= fscanf(fid,'%*i %f %f %i \n',[3,IJ] ); 

string3=fgets(fid);
II = fscanf(fid,'%i \n',1);
ns= fscanf(fid,'%*i %i \n',[1,II] )+1; 
fclose(fid);


% xs=zeros(M,N);ys=zeros(M,N);
% xs(:)=ss(1,:);ys(:)=ss(2,:);
xs=ss(1,:);ys=ss(2,:);

figure (1)
axis equal
axis off

xs1=[xs-r;xs+r;xs+r;xs-r];
ys1=[ys-r;ys-r;ys+r;ys+r];
p1=patch('XData',xs1,'YData',ys1);
p1.EdgeAlpha=0.15; 
p1.EdgeColor=[0.15 0.15 0.15];
p1.FaceColor='none';

hold on

xs2=[xs(ns)-r;xs(ns)+r;xs(ns)+r;xs(ns)-r];
ys2=[ys(ns)-r;ys(ns)-r;ys(ns)+r;ys(ns)+r];
p2=patch('XData',xs2,'YData',ys2);
p2.EdgeColor='b';
p2.FaceColor='none';

rectangle('Position',[-1,-1,2,2],'Curvature',[1 1],'EdgeColor','r');







% exportgraphics(gca,'InitialMesh.pdf','ContentType','vector')
% %saveas(f,'ff.pdf')
% open('InitialMesh.pdf')

