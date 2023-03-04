import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.offsetbox import OffsetImage, AnnotationBbox

# Load CSV file as df
df = pd.read_csv("Sprint4/data\starcraft_player_data.csv")

# Drop excess columns
drop_columns = ["GameID","SelectByHotkeys","AssignToHotkeys","MinimapAttacks","NumberOfPACs","WorkersMade","ComplexUnitsMade","ComplexAbilitiesUsed", "MinimapRightClicks", "GapBetweenPACs"]
df.drop(drop_columns, axis=1, inplace=True)

# Average and sorting
avg_df = df.groupby("LeagueIndex").mean()
avg_df = avg_df.sort_values(by="APM")

# Define dictionary mapping LeagueIndex to image filenames
index_to_image = {1: "Sprint4/images/Badges/Badges_PNG/0Bronze0.png", 2: "Sprint4/images/Badges/Badges_PNG/1Silver0.png", 3: "Sprint4/images/Badges/Badges_PNG/2Gold0.png", 4: "Sprint4/images/Badges/Badges_PNG/3Platinum0.png", 5: "Sprint4/images/Badges/Badges_PNG/4Diamond0.png", 6: "Sprint4/images/Badges/Badges_PNG/5Masters0.png", 7: "Sprint4/images/Badges/Badges_PNG/6Grandmasters1.png",8:"Sprint4/images/Badges/Badges_PNG/6Grandmasters2.png"}

# Create bar chart and style
ax = avg_df.plot(kind="barh")
ax.invert_yaxis()

# Converting blank spaces to null to capture the duplicates from our data
df.replace(r"^\s*$", np.nan, regex=True, inplace=True)

# Add images as tick labels
for i, (label, _) in enumerate(avg_df.iterrows()):
    img = plt.imread(index_to_image[label])
    imagebox = OffsetImage(img, zoom=0.3)
    ab = AnnotationBbox(imagebox, (0, i), xybox=(-20, 0), frameon=False, xycoords='data', boxcoords="offset points", pad=0)
    ax.add_artist(ab)

ax.tick_params(axis='y', length=0)
ax.set_title('Starcraft APM/League Index')
ax.set_xlabel('APM(and other actions)')
ax.set_facecolor("black")

df = df.replace('?', np.nan)
df = df.fillna(0)
df = df.astype('float')

# Second Chart (Age and Hours played per week)
age_bins = [12, 16, 20, 30, np.inf]
age_labels = ['12-16', '16-20', '20-30', '30+']
df['AgeGroup'] = pd.cut(df['Age'], bins=age_bins, labels=age_labels)
fig, ax2 = plt.subplots()

# Create a boxplot of the HoursPerWeek column, grouped by AgeGroup
df.boxplot(column='HoursPerWeek', by='AgeGroup', ax=ax2)

ax2.set_xlabel('Age Group')
ax2.set_ylabel('Hours Per Week')
ax2.set_facecolor("purple")
# Show the plot
plt.show()
