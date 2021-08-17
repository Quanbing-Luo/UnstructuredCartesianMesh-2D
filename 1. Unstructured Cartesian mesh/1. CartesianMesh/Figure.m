clear;
clf;
fid = fopen('CartesianMesh.txt','r');
string1=fgets(fid);
nps = fscanf(fid,'%i',1);
ps=fscanf(fid,'%*i %f %f \n',[2 nps]);

string2=fgets(fid);
nes = fscanf(fid,'%i',1);
MM = fscanf(fid,'%*i %i %i %i \n',[3 nes])+1;
es=MM(1:2,:);
ids=MM(3,:);

string3=fgets(fid);
nss = fscanf(fid,'%i',1);
ss=fscanf(fid,'%*i %f %f %f',[3 nss]);

% for j=1:n_elements
%  elements(1:3,j)= fscanf(fid,'%*i %i %i %i ',[3 1])+1; 
%  xPs(1,j)= fscanf(fid,'%f',1 ); 
%  yPs(1,j)= fscanf(fid,'%f',1 ); 
%  fgets(fid);        
% end
fclose(fid);


figure (1)
hold on

xs=ss(1,:);ys=ss(2,:);hs=ss(3,:);
xxs=[xs-hs;xs+hs;xs+hs;xs-hs;xs-hs;];
yys=[ys-hs;ys-hs;ys+hs;ys+hs;ys-hs;];
plot(xxs,yys, 'b'); 

xes=reshape(ps(1,es), size(es));
yes=reshape(ps(2,es), size(es));

plot(xes,yes,'r');

axis equal
axis off

% xlabel('$x$','interpreter','latex');
% ylabel('$y$','interpreter','latex');
% xlim([-1 1]);
% ylim([-1 1]);
% xticks([-1 0 1]);yticks([-1 0 1]);

% exportgraphics(gca,'InitialMesh.pdf','ContentType','vector')
% %saveas(f,'ff.pdf')
% open('InitialMesh.pdf')

