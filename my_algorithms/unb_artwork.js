function drawPart(arr,ind,ac){var l="";var p=0;
for(var i=0;i<arr.length;i++){for(var j=0;j<arr[i];j++){
l+=ac[p];}if(i==ind[0]||i==ind[1]||i==ind[2]){
l+='\n';}p==0?p=1:p=0;}return l;}function drawLogo(){
var parts={aq1:[4,4,8,4,22,13,4,4,8,4,22,15,4,4,8,4,22,4,8,4],
aq2:[4,4,8,4,4,4,1,7,6,4,7,4,4,4,8,4,4,13,5,13,4,4,8,4,4,4,6,
4,4,14],aq3:[4,4,8,4,4,4,6,4,4,4,7,5,4,5,6,5,4,4,6,4,4,4,8,5,
5,14,5,4,6,4,4,16,6,12,6,4,6,4,4,14]};var logo="";logo+=
drawPart(parts.aq1,[5,11,19],[' ','*']);logo+=
drawPart(parts.aq2,[11,19,29],[' ','*']);logo+=
drawPart(parts.aq3,[11,23,31], [' ','*']);console.log(logo);}
drawLogo();
