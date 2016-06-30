from django.db import models

#Model class
class LUser(models.Model):
    pub_date = models.DateTimeField('date published')
    userID = models.IntegerField() 
    email = models.EmailField(
                    verbose_name='email address',
                    max_length=255,
                    unique=True,
                )
    # is_active field can be used to deactivate any users ability to generate OTP
    is_active = models.BooleanField(default=True)
    phone=models.CharField(max_length=10,blank=False,null=False,default=1234567890)

    def __unicode__(self):
    	return self.email
