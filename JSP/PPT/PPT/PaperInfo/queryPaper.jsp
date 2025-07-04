<%@ page contentType="text/html; charset=GBK" language="java" import="java.sql.*" errorPage="" %>
<%@ page import="java.util.Date"%>
<%@ page import="java.text.SimpleDateFormat" %>
<jsp:useBean id="dbBean" scope="page" class="dbconn.DbConnection"/>
<jsp:useBean id="userBean" scope="session"  class="popedom.popedom"/>
<%@ include file="../checkPopedom.jsp"%>

<%!
public static String getGBString(String src) {
	try{
			if(src==null)
				return null;
			else
			{
				src = new String(src.getBytes("ISO8859_1"), "GBK");
				return src;
			}
			}catch(Exception e){
			return null;
			}

	}
%>
<%!
public static String getState(String src) {
	try{
			if(src==null)
				return null;
			else
			{
				if (src.equals("1"))
					src="<font color=blue>待审</font>" ;
				else if (src.equals("0"))
					src="<font color=red>不合格</font>" ;
				else if (src.equals("2"))
					src="<font color=green>合格</font>" ;
				else 
					src="<font color=red>非法</font>" ;
				
				return src;
			}
			}catch(Exception e){
			return null;
			}

	}
%>
<%!
public static String[] getNumber(String str)
    {
    	char[] temp=str.toCharArray();
    	int i=0;
    	int j=0;
    	String[] StringTemp={"",""};
        while(i<temp.length){
            String string = new String();
            if(temp[i]=='('){
            	i++;
            	do{
            		string+=temp[i];
            		i++;
            	}while(temp[i]!=')');
            	StringTemp[j]=string;
            	j++;
            }else {
				i++;
			}
        }
       return StringTemp;
    }
%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<LINK href="css/back.css" type=text/css rel=stylesheet>
<SCRIPT src="css/yih2.js" type=text/javascript></SCRIPT>
<SCRIPT src="css/check_form_func_lib.js" type=text/javascript></SCRIPT>
<SCRIPT src="css/yg_dom.js" type=text/javascript></SCRIPT>
<SCRIPT src="css/checkform.js" type=text/javascript></SCRIPT>
<SCRIPT language=javascript type=text/javascript>
	<!--
	function yreg_pop(s){
	window.open(s,"yec_pop3","width=520,height=500,scrollbars=yes,resizable=yes" );
	}
	// -->
</SCRIPT>
<title>论文查询</title>
</head>
<script language="JavaScript">
function  selectItem()
{
	var surl = '../user/selectUserID.jsp?';
  	var HH = screen.availHeight - 60;
  	var WW = screen.availWidth - 70;
  	var XX = event.screenX;
  	var YY = event.screenY;
  	var width = 560;
  	var height = 500;
  	var top = (YY - height - 80 > 0? YY - height - 80 : 5);
  	if (top + height > HH) { top = HH - height; }
  	var left = (XX - width/2 > 0? XX - width/2 : 10);
  	if ( left + width > WW) { left = WW - width; }
  	var sname = 'viewuser';
  	var wstr = 'scrollbars=yes,resizable=yes,width=' + width + ',height=' + height + ',top=' + top + ',left=' + left + '';
  	var newWindow=null;
	//if(!newWindow || newWindow.closed) 
	//{ 
	newWindow=window.open(surl, sname, wstr);
	//}else 
	//{ 
	newWindow.focus(); 
	//} 
}

</script>
<SCRIPT language=javascript type=text/javascript>
	
	function QueryPaper(){
	frmMain.action="queryPaper.jsp?queryFlag=1";
	frmMain.submit();
	}
	function Confirm(){
	if (!confirm("确认删除该篇文章吗?")){  
		return false;  }
	else{
		return true;  }
	
	}
</SCRIPT>
<SCRIPT language=JavaScript type=text/javascript> 
 
	var ie4 = (document.all) ? true : false;
	var ns4 = (document.layers) ? true : false;
	var ns6 = (document.getElementById && !document.all) ? true : false;
	function hidelayer(lay) {
	if (ie4) {document.all[lay].style.visibility = "hidden";}
	if (ns4) {document.layers[lay].visibility = "hide";}
	if (ns6) {document.getElementById([lay]).style.display = "none";}
	}
	function showlayer(lay) {
	if (ie4) {document.all[lay].style.visibility = "visible";}
	if (ns4) {document.layers[lay].visibility = "show";}
	if (ns6) {document.getElementById([lay]).style.display = "block";}
	}
   // -->
</SCRIPT>

<STYLE type=text/css>
.yregfloathelp {
	BORDER-RIGHT: #ffc30e 1px solid; PADDING-RIGHT: 5px; BORDER-TOP: #ffc30e 1px solid; PADDING-LEFT: 5px; FONT-SIZE: 11px; PADDING-BOTTOM: 5px; BORDER-LEFT: #ffc30e 1px solid; WIDTH: 8em; COLOR: #9c7600; PADDING-TOP: 5px; BORDER-BOTTOM: #ffc30e 1px solid; FONT-FAMILY: arial, sans-serif; BACKGROUND-COLOR: #fffbb8; TEXT-ALIGN: left
}
.table_top {
	color: #990000;
	font-weight: bold;
}

</STYLE>

<body>
<%
int ID=0;
String ObjectID="";
String Description="";
String strSQL="";
ResultSet rsTemp=null;
String PaperID="";
String PaperName="";
String MagazineName="";
String LevelID="";
String PublishYear="";
String Volume="";
String Number="";
String DepartmentID="";
String AuthorInfo="";
String DAuditingState="";
String LAuditingState="";
String DAuditingResult="";
String LAuditingResult="";
String Condition="";
String UserType="";
String Year="";

String checkFlag="";

String CYear="";
String CPrincipal="";
String CPrincipalID="";
String[] CtempPrincipal;
String CPaperName="";
String CDepartmentID="";
String CLevelID="";
		
		CYear=request.getParameter("CYear");
		if (CYear==null || CYear=="")
			CYear=userBean.getYear();
		Condition="  Year Like'%"+CYear+"%'"; 
		
		//接收查询条件
		CPaperName=getGBString(request.getParameter("CPaperName"));
		if ((CPaperName==null) || (CPaperName.equals(""))){
			CPaperName="";
			}
		else{
			Condition=Condition+" And PaperName Like'%"+CPaperName+"%'";
			}
		CPrincipal=getGBString(request.getParameter("Principal"));
		if ((CPrincipal==null) || (CPrincipal.equals("")) || (CPrincipal.equals("All"))){
			CPrincipal="";
			}
		else{
			CtempPrincipal=getNumber(CPrincipal);
			CPrincipalID=CtempPrincipal[0];
			if (CPrincipalID.equals(""))
				CPrincipalID=CPrincipal;
			Condition=Condition+" And Operator='"+CPrincipalID+"'";
			}
		
		CDepartmentID=getGBString(request.getParameter("CDepartmentID"));
		if ((CDepartmentID==null) || (CDepartmentID.equals("")) || (CDepartmentID.equals("All"))){
			//Condition=" Where Year='"+Year+"'";
			}
		else{
			Condition=Condition+" And DepartmentID='"+CDepartmentID+"'";
			}
		CLevelID=request.getParameter("CLevelID");
		if ((CLevelID==null) || (CLevelID.equals("")) || (CLevelID.equals("All"))){
			//Condition=" Where Year='"+Year+"'";
			}
		else{
			Condition=Condition+" And LevelID='"+CLevelID+"'";
			}
		
	

%>

<form name="frmMain" method="post" action="">
    <table  cellpadding=4 cellspacing=1 bordercolor=white class=open_table >
    <tbody>
      <tr>
        <td  align="center" colspan=5  bgcolor="#e5e5e5"><span  class="table_top">论文管理</span></td>
      </tr>
      <!--是否需要中文标题-->
      <tr class=tr1>
        <td width="102"> 考核年度</td>
        <td colspan="2"><input maxlength=40 size=24  name=CYear value="<%=CYear%>"></td>
        <td width="98"><span id=CnTitleLabel>第一作者</span></td>
        <td width="319"><input maxlength=40 size=24   name=Principal value="<%=CPrincipal%>">
          <input type="button" name="cmgSelect" value="选择" onClick="selectItem();">
		</td>
      </tr>
	  <tr class=tr1>
        <td width="102"><span 
      id=PostColumnLabel>论文名称&nbsp;</span></td>
        <td colspan="2"><input maxlength=40 size=24  name=CPaperName value="<%=CPaperName%>"></td>
        <td width="98">所属部门&nbsp;&nbsp; </td>
        <td><select name=CDepartmentID>
          <option value="All">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</option>
          <%
					strSQL = "select ObjectID,Description From Dic_Department Where State='1' Order By OrderID ";
					rsTemp = dbBean.executeQuery(strSQL);
					while (rsTemp.next()){
						ObjectID=rsTemp.getString("ObjectID");
						Description=(rsTemp.getString("Description")); 
			  			if (ObjectID.equals(CDepartmentID))
							checkFlag="selected";
						else
						checkFlag=""; 
			  %>
          <option value="<%=ObjectID%>" <%=checkFlag%>><%=Description%></option>
          <%}
					rsTemp.close();
					dbBean.freeCon();
					 %>
        </select></td>
	  </tr>
	  <tr class=tr1>
        <td width="102"><span id=EnKeyWordLabel>刊物级别</span>&nbsp;</td>
        <td colspan="2"><select name=CLevelID>
          <option value="All">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</option>
          <%
					strSQL = "select ObjectID,Description From Dic_PaperLevel Where State='1' Order By OrderID ";
					rsTemp = dbBean.executeQuery(strSQL);
					while (rsTemp.next()){
						ObjectID=rsTemp.getString("ObjectID");
						Description=(rsTemp.getString("Description")); 
			  			if (ObjectID.equals(CLevelID))
							checkFlag="selected";
						else
						checkFlag=""; 
			  %>
          <option value="<%=ObjectID%>" <%=checkFlag%>><%=Description%></option>
          <%}
					rsTemp.close();
					dbBean.freeCon();
					 %>
        </select></td>
        <td width="98">&nbsp;</td>
        <td>&nbsp;</td>
	  </tr>
      
	  <tr class=tr1>
        <td colspan="5">&nbsp;</td>
        </tr>
      <tr class=tr1>
        <td  colspan=5 align="center"><input type="button" name="cmdQuery" value="查 询" onClick="QueryPaper();"></td>
      </tr>
    </tbody>
  </table>
</form>

<%
String queryFlag="";
queryFlag=request.getParameter("queryFlag");
if (queryFlag!=null && queryFlag.equals("1"))
{
%> 
  <table  cellpadding=4 cellspacing=1 bordercolor=white class=open_table >
  <tr align="center" >
    <td width="4%">序号</td>
    <td width="20%">论文名称</td>
    <td width="15%">期刊名称</td>
    <td width="9%">刊物级别</td>
    <td width="7%">出版日期</td>
    <td width="4%">卷</td>
    <td width="4%">期</td>
    <td width="8%">所属部门</td>
    <td width="7%">第一作者</td>
    <td width="6%">初审</td>
    <td width="6%">终审</td>
    <td width="10%">操作</td>
    </tr>
  <%
		strSQL = "Select PaperID,PaperName,MagazineName,LevelID,PublishYear,Volume,Number,DepartmentID,DAuditingState,DAuditingResult,LAuditingState,LAuditingResult From PaperInfo Where  "+Condition+" Order By Operator" ;
		rsTemp = dbBean.executeQuery(strSQL); 
		
		if (rsTemp==null){
		}
		else{
		
		
		//循环取数据库值 
		ID=0;
		while (rsTemp.next()) 
		{ 
			ID=ID+1;
			PaperID=rsTemp.getString("PaperID");
			PaperName=(rsTemp.getString("PaperName"));
			MagazineName=(rsTemp.getString("MagazineName"));
			LevelID=(dbBean.getDescription(rsTemp.getString("LevelID"),"DIC_Paperlevel"));
			PublishYear=rsTemp.getString("PublishYear");
			Volume=rsTemp.getString("Volume");
			Number=(rsTemp.getString("Number"));
			DepartmentID=(dbBean.getDescription(rsTemp.getString("DepartmentID"),"DIC_Department"));
			DAuditingState=rsTemp.getString("DAuditingState");
			LAuditingState=rsTemp.getString("LAuditingState");
			DAuditingResult=(rsTemp.getString("DAuditingResult"));
			LAuditingResult=(rsTemp.getString("LAuditingResult"));
  %>
  <tr class="tr1" align="center">
    <td><%=ID%></td>
    <td><a href="PaperInfo.jsp?PaperID=<%=PaperID%>"><%=PaperName%></a></td>
    <td><%=MagazineName%></td>
    <td><%=LevelID%></td>
    <td><%=PublishYear%></td>
    <td><%=Volume%></td>
    <td><%=Number%></td>
    <td><%=DepartmentID%></td>
    <td><%=(dbBean.getUserName(dbBean.getFirstAuthor(PaperID),"InstituteInfo"))%></td>
    <td onMouseOver="showlayer('Dhelp_<%=ID%>')" onMouseOut="hidelayer('Dhelp_<%=ID%>')">
	<%=getState(DAuditingState)%><script language=JavaScript type=text/javascript>
		if(oBw.ie5||oBw.ns6){
			document.write("&nbsp;&nbsp;<span class=yregfloathelp style='position:absolute;style:none' id=\"Dhelp_<%=ID%>\">初审：<%=DAuditingResult%>.</span>");
		}
	</script>
	<script language=JavaScript type=text/javascript> 
		if(oBw.ie5||oBw.ns6){
			hidelayer('Dhelp_<%=ID%>') 
		}
	</script>	
	</td>
    <td onMouseOver="showlayer('Lhelp_<%=ID%>')" onMouseOut="hidelayer('Lhelp_<%=ID%>')">
	<%=getState(LAuditingState)%><script language=JavaScript type=text/javascript>
		if(oBw.ie5||oBw.ns6){
			document.write("&nbsp;&nbsp;<span class=yregfloathelp style='position:absolute;style:none' id=\"Lhelp_<%=ID%>\">终审：<%=LAuditingResult%>.</span>");
		}
	</script>
	<script language=JavaScript type=text/javascript> 
		if(oBw.ie5||oBw.ns6){
			hidelayer('Lhelp_<%=ID%>') 
		}
	</script>	
	</td>
    <td>
	<%
	if ((LAuditingState.equals("0")) || (LAuditingState.equals("1"))){
	%>
		<a href="LmodifyPaper.jsp?PaperID=<%=PaperID%>" target="_blank">修改</a>&nbsp;&nbsp;&nbsp;<a href="delPaper.jsp?PaperID=<%=PaperID%>" onClick="return Confirm();"  target="_blank">删除</a>
	<%
		}
	else{
	%>
		-锁定-
	<%
		}
	
	%>
	</td>
    </tr>
  
  <%
			
		}
		}
		rsTemp.close();
		dbBean.freeCon();
	%>
</table>
  
<%
}
%>

</body>
</html>
