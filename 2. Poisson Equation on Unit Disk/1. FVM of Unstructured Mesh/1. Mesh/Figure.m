clear;
clf;
fid = fopen('mesh.txt','r');
string1=fgets(fid);
n_nodes = fscanf(fid,'%i',1);
nodes= fscanf(fid,'%*i %f %f \n',[2 n_nodes]);

string2=fgets(fid);
n_elements = fscanf(fid,'%i',1);
elements = fscanf(fid,'%*i %i %i %i \n',[3 n_elements])+1;

fclose(fid);

figure (1)

%pdemesh(nodes,elements);
pdemesh(nodes,elements,'ElementLabels','on');
%pdemesh(nodes,elements,'NodeLabels','on');
xlabel('$x$','interpreter','latex');
ylabel('$y$','interpreter','latex');
xlim([-1 1]);
ylim([-1 1]);
xticks([-1 0 1]);yticks([-1 0 1]);

