<%@ page language="java" import="xiaoxiang.fileUpload.*"%>
<%@ page contentType="text/html;charset=gb2312"%>
<%@ page errorPage="error.jsp"%>
<%@ page import="java.io.File"%>

<!-- 初始化一个upBean-->
<jsp:useBean id="myUpload" scope="page" class="xiaoxiang.fileUpload.upBean" />


<%
	//初始化工作
	myUpload.initialize(pageContext);
	
	//设定允许的文件后缀名
	myUpload.setAllowedExtList("gif,jpg");

	//设定允许上传的文件类型
	//gif:gif
	//jpg:pjpeg
	//text:plain
	//html:html
	//doc:msword
	myUpload.setAllowedFileTypeList("gif,pjpeg");

	//设定是否允许覆盖服务器上的同名文件
	myUpload.setIsCover(false);
	
	//设定允许上传文件的总大小
	//myUpload.setTotalMaxFileSize(1000000);

	//设定单个文件大小的限制
	//myUpload.setMaxFileSize(100000);

	String[] sourceName={"",""};		//文件的原始文件名数组
	String myName=new String("");	
	
	//设定上传的物理路径
	myUpload.setRealPath(application.getRealPath(File.separator+"example"+File.separator+"e1_uploadFiles"));

	try
	{
			//将所有数据导入组件的数据结构中
			myUpload.upload();
	}
	catch(Exception e){throw e;}

	//得到所有上传的文件
	files myFiles=myUpload.getFiles();


	//将文件保存到服务器
	try
		{

			for(int i=0;i<myFiles.getCount();i++)
			{
				myName="myName";
				myName=myName+"_"+i+"."+myFiles.getFile(i).getExtName();
				sourceName[i]=myFiles.getFile(i).getName();
				myFiles.getFile(i).setName(myName);
				//有两种保存方法，一种是保存在myUpload.setRealPath()的设定路径中，使用saveAs()，一种是另外保存到其他文件夹,使用.saveAs(String realPath)
				myFiles.getFile(i).saveAs();
			}
		}
	catch (Exception e) {throw e;}

%>

<html>
	<head>
	<title>上传结果</title>
		<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
		<meta http-equiv="expires" content="fri,30 dec 1999 00:00:00 gmt">
		<meta name="author" content="fredwebs@sina.com">
		<link rel='stylesheet' href='style.css' type='text/css'>
	</head>
	<body bgcolor="#999999" style="margin:0;">
		<table border="0" cellspacing="0" cellpadding="0" width="778" height="100%" align=center style="border-right:1 solid black;border-left:1 solid black;">
			<tr>
				<td valign=top bgcolor="#D6EAFF">
					<table border="0" cellspacing="0" cellpadding="0" width="100%">
						<tr>
							<td background="image/top_bg.gif" style="padding-left:39">
								<img src="image/title.gif" border=0></td>
						</tr>
						<tr><td height="11" bgcolor="#ffffff"></td></tr>
						<tr>
							<td style="padding-top:20;">
								<div ><img src="image/example_title.gif" border=0></div><br><br>
								<table border="0" cellspacing="1" cellpadding="5" width="500" align=center bgcolor="#3A6EA5">
									<th style="color:white" colspan=2>潇湘JSP上传组件示例</th>
									<tr bgcolor="#FFFFCC">
										<td colspan=2>与上传的文件相关的信息</td>
									</tr>
									<tr bgcolor="#ffffff">
										<td bgcolor="#C4DFFB">共上传文件数</td>
										<td bgcolor="#E9F4FF"><%out.print(myFiles.getCount());%></td>
									</tr>
									<tr bgcolor="#ffffff">
										<td bgcolor="#C4DFFB">原文件名：</td>
										<td bgcolor="#E9F4FF">
											<%
											for(int i=0;i<sourceName.length;i++)
											{
												out.print(sourceName[i]);
												out.print("<br>");
											}
											%>
										</td>
									</tr>
									<tr bgcolor="#ffffff">
										<td bgcolor="#C4DFFB">存到服务器上的文件名：</td>
										<td bgcolor="#E9F4FF">
											<%
											for(int i=0;i<myFiles.getCount();i++)
											{
												out.print(myFiles.getFile(i).getName()+"("+(myFiles.getFile(i).getSize()/1000+1)+"kb)");
												out.print("<br>");
											}
											%>	
										</td>
									</tr>
									<tr>
										<td bgcolor="#C4DFFB">文件总共大小：</td>
										<td bgcolor="#E9F4FF">
											<%=(myFiles.getSize()/1000+1)+"kb"%></td>
									</tr>
									<tr bgcolor="#FFFFCC">
										<td colspan=2>与上传页面其他控件相关的信息</td>
									</tr>
									<tr bgcolor="#ffffff">
										<td  bgcolor="#C4DFFB">文件名</td>
										<td bgcolor="#E9F4FF">
										<%=myUpload.getRequest().getParameter("fileName")%></td>
									</tr>
									<tr bgcolor="#ffffff">
										<td  bgcolor="#C4DFFB">文件密码</td>
										<td bgcolor="#E9F4FF">
											<%=myUpload.getRequest().getParameter("pwd")%></td>
									</tr>
									<tr bgcolor="#ffffff">
										<td  bgcolor="#C4DFFB">文件描述</td>
										<td bgcolor="#E9F4FF">
											<%=myUpload.getRequest().getParameter("description")%></td>
									</tr>
									<tr bgcolor="#ffffff">
										<td  bgcolor="#C4DFFB">文件包括</td>
										<td bgcolor="#E9F4FF">
										<%
											String[] fileContent=myUpload.getRequest().getParameterValues("fileContent");
											if(fileContent!=null)
											{
											for(int i=0;i<fileContent.length;i++)
											out.print(fileContent[i]+"<br>");
											}
											else
											out.print("null");
										%>
										</td>
									</tr>
									<tr bgcolor="#ffffff">
										<td  bgcolor="#C4DFFB">文件类型</td>
										<td bgcolor="#E9F4FF">
											<%=myUpload.getRequest().getParameter("fileType")%></td>
									</tr>
								</table>
								<BR><BR>
							</td>
						</tr>

					</table>
					<BR><BR><BR>
					<div style="text-indent:2em;height:30">本组件由<FONT  COLOR="#990000">潇湘工作室</FONT>(<A HREF="http://xiaoxiang.net" target="_blank">www.xiaoxiang.net</A>)开发，可免费在网上传播使用.</div>
				</td>
				<td width="11" bgcolor="#ffffff"></td>
				<td width="132" background="image/right_bg.gif"></td>
			</tr>
		</table>
	</body>
</html>