<%@ page contentType="text/html;charset=gb2312"%>
<%@ page isErrorPage="true"%>
<html><title>Error occured!</title>
		<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
		<meta http-equiv="expires" content="fri,30 dec 1999 00:00:00 gmt">
		<meta name="author" content="fredwebs@sina.com">
		<link rel='stylesheet' href='style.css' type='text/css'>
	</head>
	<body bgcolor="#999999" style="margin:0;">
		<table border="0" cellspacing="0" cellpadding="0" width="778" height="100%" align=center style="border-right:1 solid black;border-left:1 solid black;">
			<tr>
				<td valign=top bgcolor="#D6EAFF">
					<table border="0" cellspacing="0" cellpadding="0" width="100%" height="80%">
						<tr>
							<td background="image/top_bg.gif" style="padding-left:39" height="115">
								<img src="image/title.gif" border=0></td>
						</tr>
						<tr><td height="11" bgcolor="#ffffff"></td></tr>
						<tr>
							<td style="padding-top:20;" valign=top>
								<div ><img src="image/example_title.gif" border=0></div>
								<br><br><br><br><br>
									<table border="0" cellspacing="1" cellpadding="5" width="500" align=center bgcolor="#3A6EA5">
										<tr>
											<td style="color:white;">
												You had an error:<br>
												<%=exception.toString()%><BR><BR>
												Please <A HREF="javascript:history.back(-1);" style="text-decoration:underline;"><FONT COLOR="#333333">go back</FONT></A>.
											</td>
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