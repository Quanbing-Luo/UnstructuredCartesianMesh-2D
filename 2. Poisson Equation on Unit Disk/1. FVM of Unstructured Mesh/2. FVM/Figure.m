clear;
clf;
fid = fopen('FVM.txt','r');
string1=fgets(fid);
n_nodes = fscanf(fid,'%i',1);
nodes=fscanf(fid,'%*i %f %f \n',[2 n_nodes]);

string2=fgets(fid);
n_elements = fscanf(fid,'%i',1);
MM = fscanf(fid,'%*i %i %i %i %f %f %f \n',[6 n_elements]); 

elements=MM(1:3, 1:n_elements)+1;
xPs=MM(4, 1:n_elements);
yPs=MM(5, 1:n_elements);
TPs=MM(6, 1:n_elements);
% for j=1:n_elements
%  elements(1:3,j)= fscanf(fid,'%*i %i %i %i ',[3 1])+1; 
%  xPs(1,j)= fscanf(fid,'%f',1 ); 
%  yPs(1,j)= fscanf(fid,'%f',1 ); 
%  TPs(1,j)= fscanf(fid,'%f',1 ); 
%  rPs(1,j)= fscanf(fid,'%f',1 ); 
%  APs(1,j)= fscanf(fid,'%f',1 ); 
%  aPs(1,j)= fscanf(fid,'%f',1 );
%  fgets(fid);        
% end
fclose(fid);

T = (1 - xPs.^2 - yPs.^2)/4;
errT=T-TPs;
MerrT=mean(abs(errT));

figure (1)
pdemesh(nodes,elements);
%pdemesh(nodes,elements,'ElementLabels','on');
%pdemesh(nodes,elements,'NodeLabels','on','ElementLabels','on');
hold on 
plot(xPs,yPs,'o');


figure (2)
pdeplot(nodes,elements,'XYData',TPs,'ZData',TPs);

figure (3)
pdeplot(nodes,elements,'XYData',errT);
hold on
rectangle('Position',[-1,-1,2,2],'Curvature',[1 1],'EdgeColor','r');
axis equal
% xlabel('$x$','interpreter','latex');
% ylabel('$y$','interpreter','latex');
% xlim([-1 1]);
% ylim([-1 1]);
% xticks([-1 0 1]);yticks([-1 0 1]);



