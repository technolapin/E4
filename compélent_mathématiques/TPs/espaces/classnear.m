function [M] = classnear(X,X1,X2)
  M=[];
  d= size(X1,1);
  for i=1:size(X,1)
	x=X(i,:);
	y1=min((X1-ones(d,1)*x).^2*ones(size(X,2),1));
	y2=min((X2-ones(d,1)*x).^2*ones(size(X,2),1));
	M=[M; [uint32(i) y1 y2 (y1<y2)]];
  end 
end
