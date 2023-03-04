import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.offsetbox import OffsetImage, AnnotationBbox
df2 = pd.read_csv("Sprint4/data\starcraft_player_data.csv")

# Replace "?" with NaN and drop rows with NaN values
df2 = df2.replace('?', pd.np.nan).dropna()

# Group the DataFrame by the "LeagueIndex" column and calculate the mode of the "Age" column within each group
age_mode_by_league_index = df2.groupby('LeagueIndex')['Age'].apply(lambda x: x.mode()[0])

# Create a bar chart of the mode of age by LeagueIndex
plt.bar(age_mode_by_league_index.index, age_mode_by_league_index.values)

# Add labels and title
plt.xlabel('League Index')
plt.ylabel('Most common age')
plt.title('Most Common Age by League Index')

# Show the plot
plt.show()