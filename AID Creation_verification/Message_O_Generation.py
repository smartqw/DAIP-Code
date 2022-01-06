no_of_nominee=10
file_PseudoID_tilda=open("Pseudo_ID_tilda.txt", "r")
file_message_o=open("message_o_"+str(no_of_nominee)+".txt", "w")
User_ID="12345600000000000000"
Organization="www.facebook.com"
Account ="987654321012345"
nominee_id=["123456789", "987654321", "1234566789", "234567891000", "435654321123456","34567543212345", "5647354213234567", "345267123456543","23124563124356", "987654321123"]
relationship_id=["Brother", "Brother", "Brother", "Sister", "Sister","Sister", "Sister", "Brother-Son", "Brother-Son", "Brother-Son"]

next(file_PseudoID_tilda)
file_message_o.write("The pseduo id tilda of user is \n")
file_message_o.write(next(file_PseudoID_tilda))
file_message_o.write("\n"+"The account ID is \n" + Account + "\n" + "The Organization name is \n"+ Organization)
i=0
while i< no_of_nominee:
 file_message_o.write("\n" + "the ID of nominee is \n"+ nominee_id[i] +"\nthe relation with user is \n"+ relationship_id[i] +"\npreferance level is \n"+str(i+1))
 i=i+1
    



