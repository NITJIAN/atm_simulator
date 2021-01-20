import smtplib
from email.message import EmailMessage
msg = EmailMessage()
msg['Subject'] = 'From my script'
msg['From'] = 'environmentseekersnitj@gmail.com'
msg['To'] = 'sanujsood@gmail.com'
smtp = smtplib.SMTP_SSL('smtp.gmail.com', 465)
smtp.login('environmentseekersnitj@gmail.com', 'fdgphlhigarggaoy')
msg.set_content('Your OTP for verification of booking is given as :: 13639')
smtp.send_message(msg)
smtp.quit()