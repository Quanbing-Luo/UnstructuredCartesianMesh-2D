clear;
clf;
fid = fopen('Geometry.txt');
string1=fgets(fid);
nps = fscanf(fid,'%i',1);
ps= fscanf(fid,'%*i %f %f\n',[2 nps]);


string3=fgets(fid);
nes = fscanf(fid,'%i',1);
MM = fscanf(fid,'%*i %i %i %i %i \n',[4 nes]);
es=MM(1:2,:) +1;
ids=MM(3,:);
fclose(fid);

xes=reshape(ps(1,es), size(es));
yes=reshape(ps(2,es), size(es));

figure (1)
plot(xes,yes,'k',xes,yes,'bo');

axis equal
% 
% viscircles(ps',r','LineWidth',1);
