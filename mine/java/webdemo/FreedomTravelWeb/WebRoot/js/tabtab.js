function Pid(id,tag){
	if(!tag){
		return document.getElementById(id);
		}
	else{
		return document.getElementById(id).getElementsByTagName(tag);
		}
}

function tab(id,hx,box,iClass,s,pr){
	var hxs=Pid(id,hx);
	var boxs=Pid(id,box);
	if(!iClass){ // �����ָ��class����
		boxsClass=boxs; // ֱ��ʹ��box��Ϊ����
	}
	else{ // ���ָ��class����
		var boxsClass = [];
		for(i=0;i<boxs.length;i++){
			if(boxs[i].className.match(/\btab\b/)){// �ж�������classƥ��
				boxsClass.push(boxs[i]);
			}
		}
	}
	if(!pr){ // �����ָ��Ԥչ����������
		go_to(0); // Ĭ��չ������
		yy();
	}
	else {
		go_to(pr);
		yy();
	}
	function yy(){
		for(var i=0;i<hxs.length;i++){
			hxs[i].temp=i;
			if(!s){// �����ָ���¼�����
				s="onmouseover"; // ʹ��Ĭ���¼�
				hxs[i][s]=function(){
					go_to(this.temp);
				}
			}
			else{
				hxs[i][s]=function(){
					go_to(this.temp);
				}
			}
		}
	}
	function go_to(pr){
		for(var i=0;i<hxs.length;i++){
			if(!hxs[i].tmpClass){
				hxs[i].tmpClass=hxs[i].className+=" ";
				boxsClass[i].tmpClass=boxsClass[i].className+=" ";
			}
			if(pr==i){
				hxs[i].className+=" up"; // չ��״̬������
				boxsClass[i].className+=" up"; // չ��״̬������
			}
			else {
				hxs[i].className=hxs[i].tmpClass;
				boxsClass[i].className=boxsClass[i].tmpClass;
			}
		}
	}
}
tab("tab02","h3","div","","onclick",0); 